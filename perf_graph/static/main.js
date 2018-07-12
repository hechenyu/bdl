anychart.onDocumentReady(function () {
  // create data set on our data
  chartData = {
    title: 'performance of data loader',
    header: this.order,
    rows:Object.values(this.data)
  };
  console.log(Object.values(this.data))

  // create column chart
  var chart = anychart.column();

  // set chart data
  chart.data(chartData);

  // turn on chart animation
  chart.animation(true);

  chart.yAxis().labels().format('{%Value}{groupsSeparator: }');

  // set titles for Y-axis
  chart.yAxis().title('IO rate');
  chart.xAxis().title('Read type')

  chart.labels()
    .enabled(true)
    .position('center-top')
    .anchor('center-bottom')
    .format('{%Value}{groupsSeparator: }MB/s');
  chart.hovered().labels(false);

  // turn on legend and tune it
  chart.legend()
    .enabled(true)
    .fontSize(13)
    .padding([0, 0, 20, 0]);

  // interactivity settings and tooltip position
  chart.interactivity().hoverMode('single');

  chart.tooltip()
    .positionMode('point')
    .position('center-top')
    .anchor('center-bottom')
    .offsetX(0)
    .offsetY(5)
    .titleFormat('{%X}')
    .format('{%SeriesName} : {%Value}{groupsSeparator: }');

  // set container id for the chart
  chart.container('container');

  // initiate chart drawing
  chart.draw();
});