// ==UserScript==
// @name        pixiv_search_ranking_change_to_be_able_to_click
// @namespace   pixiv_search
// @description pixivでランキングのやつ（料金広告）を外して、クリックできるようにする。
// @include     http://www.pixiv.net/search.php*
// @version     1
// @grant       none
// ==/UserScript==
$('.popular-introduction-block').remove();
