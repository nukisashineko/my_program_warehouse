// ==UserScript==
// @name         DisplayedTweetsCounterOnWebClient
// @namespace    http://tampermonkey.net/
// @version      0.1
// @description  読み込んだツイート数を公式webクライアント上に表示する
// @author       nukisashineko
// @match        https://twitter.com/*
// @grant        none
// ==/UserScript==



function make_element_from_html_string(str){
    var div = document.createElement('body');
    div.innerHTML = str;
    var element = div.firstElementChild;
    return element;
}
function update_displaying_tweet_count(){
    if(document.getElementById("displaying_tweet_count") !== null ){
        document.getElementById("displaying_tweet_count").innerHTML=document.querySelectorAll('.tweet').length;
    }
    setTimeout(update_displaying_tweet_count,1000);
}

function ready_func (){
    if(document.location.href === "https://twitter.com/"){
        let str = `
<li class="DisplayedTweetsCount">
<a role="button" href="#" class="js-tooltip js-dynamic-tooltip global-dm-nav" data-placement="bottom" data-original-title="">
<span class="Icon Icon--large" ><font style="font-size: 12px;">📖</font></span>
<span class="text"  id="displaying_tweet_count"></span>
</a>
</li>

`;
        let element = make_element_from_html_string(str);
        document.querySelector('ul#global-actions').appendChild(element);
        update_displaying_tweet_count();

    }else if(document.querySelector('.ProfileNav-list') !== null){

        let str = `
<li class="ProfileNav-item ProfileNav-item--favorites DisplayedTweetsCount" data-more-item=".ProfileNav-dropdownItem--favorites">
<a class="ProfileNav-stat ProfileNav-stat--link u-borderUserColor u-textCenter js-tooltip js-nav u-textUserColor" >
<span class="ProfileNav-label">表示ツイート数</span>
<span class="ProfileNav-value" data-is-compact="false" id="displaying_tweet_count">??</span>
</a>
</li>
`;
        let element = make_element_from_html_string(str);
        document.querySelector('ul.ProfileNav-list').appendChild(element);
        update_displaying_tweet_count();

    }
}
if( window.addEventListener ){
    window.addEventListener('load', ready_func);
}else if( window.attachEvent ){
    window.attachEvent('onload', ready_func);
}


// href_update_check twitter use turbolinks
(function(){
    var current_url = document.location.href;
    (function href_update_check(){
        if(current_url !== document.location.href){
            let my_li_element = document.querySelector('.DisplayedTweetsCount');
            if(my_li_element !== null){
                my_li_element.parentNode.removeChild(my_li_element);
            }
            current_url = document.location.href;
            ready_func();
        }
        setTimeout(href_update_check,1000);
    })();
})();
