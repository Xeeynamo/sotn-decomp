import React, { useEffect, useState, useRef } from 'react';
import { Chart } from './Chart';

export const ChartsVersion = ({
    gameId,
    version,
    labels,
    overlays,
}) => {
    const renderOvlChart = function (overlayId, history, ovlCode, ovlFuncs) {
        const wholeTimeline = history.map(x => x.timestamp);
        const length = Math.min(Math.min(ovlCode.length, ovlFuncs.length), wholeTimeline.length);

        if (length === 0) {
            return;
        }

        const timeline = [wholeTimeline[wholeTimeline.length - 1]];
        const funcs = [ovlFuncs[ovlFuncs - 1]];
        const code = [ovlCode[ovlCode - 1]];
        var prevFuncs = funcs[0];
        for (var i = length - 2; i >= 0; i--) {
            if (!isNaN(ovlFuncs[i]) && prevFuncs !== ovlFuncs[i]) {
                prevFuncs = ovlFuncs[i]
                timeline.push(wholeTimeline[i])
                funcs.push(ovlFuncs[i])
                code.push(ovlCode[i])
            }
        }

        timeline.reverse();
        funcs.reverse();
        code.reverse();

        // add the current date with the last entry values
        // to fill the remaining space.
        timeline.unshift(new Date().getTime() / 1000)
        funcs.unshift(funcs[0])
        code.unshift(code[0])

        const ovlMeta = overlays[overlayId];
        const data = [
            timeline,
            funcs,
            code,
        ]
        return (
            <div>
                <p className="chartOvlTitle">{ovlMeta.name}</p>
                <span className="chartOvlDesc">{ovlMeta.desc}</span>
                <Chart data={data} />
            </div>
        )
    }

    const labelCode = labels[0].id;
    const labelFunctions = labels[1].id;
    const versionId = version.id
    const [progressCode, setProgressCode] = useState(undefined)
    const [progressFuncs, setProgressFuncs] = useState(undefined)

    const progressFetchingRef = useRef(false);
    useEffect(() => {
        const getEntryProgress = function (name, entry) {
            return entry[name] / entry[`${name}/total`]
        }
        const normaliseData = function (data, slug, ver, type) {
            const src = data[slug][ver][type]
            const timeline = src.map(x => ({
                timestamp: x.timestamp,
                gitHash: x.git_hash,
            }))

            // This piece of code used to obtain the list of overlays from the
            // server rather than from the game metadata
            // const overlays = Object.keys(src[0].measures)
            //     .map(x => x.split('/')[0])
            //     .filter((v, idx, a) => a.indexOf(v) === idx)

            return {
                timeline: timeline,
                overlays: version.overlays.map(ovl => ({
                    name: ovl,
                    percentage: src.map(x => getEntryProgress(ovl, x.measures))
                }))
            }
        }
        const fetchProgress = async (type, setter) => {
            const host = "https://progress.deco.mp"
            const url = `${host}/data/${gameId}/${versionId}/${type}/?mode=all`
            const response = await fetch(url);
            const data = await response.json();
            return setter(normaliseData(data, gameId, versionId, type));
        }
        if (progressFetchingRef.current !== true) {
            progressFetchingRef.current = true;
            progressCode ?? fetchProgress(labelCode, setProgressCode);
            progressFuncs ?? fetchProgress(labelFunctions, setProgressFuncs);
        }
    }, [
        gameId, versionId, version,
        labelCode, labelFunctions,
        progressCode, progressFuncs,
        progressFetchingRef
    ]);

    const progressCharts = ((progressCode || progressFuncs) &&
        (progressCode ?? progressFuncs).overlays.map(ovl => {
            console.log(ovl);
            const timeline = (progressCode ?? progressFuncs).timeline
            const code = progressCode != null ? progressCode.overlays
                .filter(x => x.name === ovl.name)[0].percentage : [];
            const funcs = progressFuncs != null ? progressFuncs.overlays
                .filter(x => x.name === ovl.name)[0].percentage : []
            return renderOvlChart(ovl.name, timeline, code, funcs)
        }))

    return (
        <div className="ChartsVersion">
            <h2>Progress for {version.name}</h2>
            <center>{progressCharts}</center>
        </div>)
}
