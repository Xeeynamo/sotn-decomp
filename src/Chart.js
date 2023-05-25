import React from 'react';
import uPlot from 'uplot';
import UplotReact from 'uplot-react';
import 'uplot/dist/uPlot.min.css';

export const Chart = ({
    data,
}) => {
    const toPercent = function (x) {
        return x ? x.toLocaleString(undefined, { style: 'percent', minimumFractionDigits: 2 }) : "--"
    }

    const options = {
        width: 800,
        height: 400,
        series: [
            {
                label: "Date"
            },
            {
                label: "Functions",
                points: { show: true },
                width: 1.5,
                stroke: "rgba(255, 255, 0, 1)",
                fill: "rgba(255, 255, 0, 0.3)",
                value: (self, value) => toPercent(value)
            },
            {
                label: "Code",
                points: { show: true },
                width: 1.5,
                stroke: "rgba(255, 0, 0, 1)",
                fill: "#FF2D24A0",
                value: (self, value) => toPercent(value)
            },
        ],
        scales: {
            x: {
                time: true,
            },
            y: {
                range: [0, 1]
            }
        },
        axes: [
            {
                stroke: "#c7d0d9",
                grid: {
                    width: 1 / devicePixelRatio,
                    stroke: "#2c3235",
                },
                ticks: {
                    width: 1 / devicePixelRatio,
                    stroke: "#2c3235",
                },
            },
            {
                stroke: "#c7d0d9",
                grid: {
                    width: 1 / devicePixelRatio,
                    stroke: "#2c3235",
                },
                ticks: {
                    width: 1 / devicePixelRatio,
                    stroke: "#2c3235",
                },
                values: (self, ticks) => ticks.map(x => x * 100 + "%"),
            },
        ]
    }
    const target = null

    return (<UplotReact
        options={options}
        data={data}
        target={target}
        onCreate={(chart) => { }}
        onDelete={(chart) => { }}
    />);
}
