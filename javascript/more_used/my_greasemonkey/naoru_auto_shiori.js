// ==UserScript==
// @name        narou_auto_shiori
// @namespace   narou_auto_shiori
// @description なろうに自動的に栞を挟む
// @include     http://ncode.syosetu.com/*/*/
// @require http://ajax.googleapis.com/ajax/libs/jquery/1.5.2/jquery.min.js
// @version     1
// @grant       GM_xmlhttpRequest
// ==/UserScript==
if ($('.bookmark_now a')[0]) {
  var shiori = $('.bookmark_now a').attr('href')
  console.log(shiori);
  GM_xmlhttpRequest({
    method: 'GET',
    url: shiori,
    onload: function (response) {
      console.log(response);
    }
  });
}
