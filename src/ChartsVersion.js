import React, { useEffect, useState } from 'react';
import { Chart } from './Chart';

export const ChartsVersion = ({
    gameVersion,
    name,
}) => {
    const getEntryProgress = function(name, entry) {
        return entry[name] / entry[`${name}/total`]
    }

    const normaliseData = function(data, slug, ver, type) {
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

    const renderOvlChart = function(name, timeline, ovlCode, ovlFuncs)  {
        const data = [
            timeline.map(x => x.timestamp),
            ovlFuncs,
            ovlCode,
          ]
        return (
            <Chart moduleName={name} data={data}/>
        )
    }

    const [progressCode, setProgressCode] = useState(undefined)
    const [progressFuncs, setProgressFuncs] = useState(undefined)

    const fetchProgress = async (type, setter) => {
      const host = "https://progress.deco.mp"
      const url = `${host}/data/sotn/${gameVersion}/${type}/?mode=all`
      const response = await fetch(url);
        const data = await response.json();
        return setter(normaliseData(data, "sotn", gameVersion, type));
    }
  
    useEffect(() => {
        fetchProgress('code', setProgressCode);
        fetchProgress('functions', setProgressFuncs);
    },[fetchProgress])

    const progressCharts = (progressCode && progressFuncs &&
        progressCode.overlays.map(ovl => {
            const timeline = progressCode.timeline
            const code = progressCode.overlays
                .filter(x => x.name === ovl.name)[0].percentage
            const funcs = progressFuncs.overlays
                .filter(x => x.name === ovl.name)[0].percentage
            return renderOvlChart(ovl.name, timeline, code, funcs)
        }))

    return (
        <div>
            <h2>Progress for {name}</h2>
            <center>{progressCharts}</center>
        </div>)
}
