anychart.onDocumentReady(function () {
    // create line chart
    var chart = anychart.line();

    // set chart padding
    chart.padding([10, 20, 5, 20]);

    // turn on chart animation
    chart.animation(true);

    // turn on the crosshair
    chart.crosshair(true);

    // set chart title text settings
    chart.title(this.loader + ' IO test');

    // set y axis title
    chart.yAxis().title('MB/s');

    // create logarithmic scale
    var logScale = anychart.scales.log();


    // set scale for the chart, this scale will be used in all scale dependent entries such axes, grids, etc
    chart.yScale(logScale);

    // create data set on our data,also we can pud data directly to series
    var dataSet = anychart.data.set(this.data);

    var seriesData_1 = dataSet.mapAs({
        'x': 0,
        'value': 1
    });

    var seriesData_2 = dataSet.mapAs({
        'x': 0,
        'value': 2
    });

    var seriesData_3 = dataSet.mapAs({
        'x': 0,
        'value': 3
    });
    var seriesData_4 = dataSet.mapAs({
        'x': 0,
        'value': 4
    });
    var seriesData_5 = dataSet.mapAs({
        'x': 0,
        'value': 5
    }); // temp variable to store series instance
    var seriesData_6 = dataSet.mapAs({
        'x': 0,
        'value': 6
    })
    var series;

    // setup first series
    series = chart.line(seriesData_1);
    series.name('seq-hdd');
    // enable series data labels
    series.labels()
        .enabled(true)
        .anchor('left-bottom')
        .padding(5);
    // enable series markers
    series.markers(true);

    // setup second series
    series = chart.line(seriesData_2);
    series.name('seq-ssd');
    // enable series data labels
    series.labels()
        .enabled(true)
        .anchor('left-bottom')
        .padding(5);
    // enable series markers
    series.markers(true);

    // setupo third series
    series = chart.line(seriesData_3);
    series.name('ran-hdd');
    // enable series data labels
    series.labels()
        .enabled(true)
        .anchor('left-bottom')
        .padding(5);
    // enable series markers
    series.markers(true);

    // setup second series
    series = chart.line(seriesData_4);
    series.name('ran-ssd');
    // enable series data labels
    series.labels()
        .enabled(true)
        .anchor('left-bottom')
        .padding(5);
    // enable series markers
    series.markers(true);

    // setupo third series
    series = chart.line(seriesData_5);
    series.name('std-hdd');
    // enable series data labels
    series.labels()
        .enabled(true)
        .anchor('left-bottom')
        .padding(5);
    // enable series markers
    series.markers(true);

    // setup second series
    series = chart.line(seriesData_6);
    series.name('std-ssd');
    // enable series data labels
    series.labels()
        .enabled(true)
        .anchor('left-bottom')
        .padding(5);
    // enable series markers
    series.markers(true);

    // turn the legend on
    chart.legend()
        .enabled(true)
        .fontSize(13)
        .padding([0, 0, 20, 0]);

    // set container for the chart and define padding
    chart.container('container');
    // initiate chart drawing
    chart.draw();
});