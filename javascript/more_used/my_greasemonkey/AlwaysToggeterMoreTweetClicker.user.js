// ==UserScript==
// @name         AlwaysToggeterMoreTweetClicker
// @namespace    http://tampermonkey.net/
// @version      0.1
// @description  this code do click "残りを読む"
// @author       nukisashineko
// @match        https://togetter.com/li/*
// @grant        none
// ==/UserScript==

(function() {
    'use strict';
    document.querySelector('.more_tweet_box').children[0].click();
})();
