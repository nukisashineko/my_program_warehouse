// ==UserScript==
// @name        u-aizu.gpa.popup
// @namespace   u-aizu.gpa.popup
// @include     https://csweb.u-aizu.ac.jp/campusweb/campussquare.do?_flowExecutionKey=*
// @version     1
// @grant       none
// @require http://ajax.googleapis.com/ajax/libs/jquery/1.5.2/jquery.min.js
// ==/UserScript==
$(document).ready(function () {
  Grades = $('table.normal tr>td:nth-child(8)').map(function () {
    switch ($(this).text().replace(/\s/g, '')) {
      case 'A':
        return 4;
      case 'B':
        return 3;
      case 'C':
        return 2;
      case 'D':
      case '放棄':
        return 0;
    }
  }).get()
  sum = Grades.reduce(function (x, y) {
    return x + y
  })
  GPA = sum / Grades.length
  alert('GPA:' + Math.round(GPA * 1000) / 1000)
});
