import React, { useEffect, useState, useRef } from 'react';
import { Chart } from './Chart';

export const ChartsVersion = ({
    gameId,
    version,
    labels,
    overlays,
}) => {
    const getEntryProgress = function (name, entry) {
        return entry[name] / entry[`${name}/total`]
    }

    const normaliseData = function (data, slug, ver, type) {
        const src = data[slug][ver][type]
        const timeline = src.map(x => ({
            timestamp: x.timestamp,
            gitHash: x.git_hash,
        }))
        const overlays = Object.keys(src[0].measures)
            .map(x => x.split('/')[0])
            .filter((v, idx, a) => a.indexOf(v) === idx)

        return {
            timeline: timeline,
            overlays: overlays.map(ovl => ({
                name: ovl,
                percentage: src.map(x => getEntryProgress(ovl, x.measures))
            }))
        }
    }

    const renderOvlChart = function (name, timeline, ovlCode, ovlFuncs) {
        const data = [
            timeline.map(x => x.timestamp),
            ovlFuncs,
            ovlCode,
        ]
        return (
            <Chart moduleName={name} data={data} />
        )
    }

    const labelCode = labels[0].id;
    const labelFunctions = labels[1].id;
    const versionId = version.id
    const [progressCode, setProgressCode] = useState(undefined)
    const [progressFuncs, setProgressFuncs] = useState(undefined)

    const progressFetchingRef = useRef(false);
    useEffect(() => {
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
        gameId, versionId,
        labelCode, labelFunctions,
        progressCode, progressFuncs,
        progressFetchingRef,
        normaliseData
    ]);

    const progressCharts = ((progressCode || progressFuncs) &&
        (progressCode ?? progressFuncs).overlays.map(ovl => {
            const timeline = (progressCode ?? progressFuncs).timeline
            const code = progressCode != null ? progressCode.overlays
                .filter(x => x.name === ovl.name)[0].percentage : [];
            const funcs = progressFuncs != null ? progressFuncs.overlays
                .filter(x => x.name === ovl.name)[0].percentage : []
            return renderOvlChart(ovl.name, timeline, code, funcs)
        }))

    return (
        <div>
            <h2>Progress for {version.name}</h2>
            <center>{progressCharts}</center>
        </div>)
}
