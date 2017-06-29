require 'bundler'
Bundler.require


# USER_DATA = { mail: "XXXXXXX", password: "XXXXXXXXXXX"}
USER_DATA = YAML.load_file("./narou_password.yml")

#お気に入りのページを渡されるとそのカテゴリから全てのncodeを抽出する
def get_ncode_all_from_favorite_page(agent,favorite_page_link)
  agent.get(favorite_page_link) do |favorite_page|
    ncode_list = favorite_page.search('table.favnovel a.title').map do |novel_a_tag|
      novel_a_tag.get_attribute(:href).match(/http:\/\/ncode.syosetu.com\/(.*?)\//) do |match_data|
        match_data[1]
      end
    end
    if next_page = favorite_page.at('[title="next page"]')
      return ncode_list + get_ncode_all_from_favorite_page(agent,next_page.get_attribute(:href))
    else
      return ncode_list
    end
  end
end

# お気に入りのカテゴリ名をキーにしたncode配列を取得
def get_favorite_ncodes(agent)
  agent.get("http://syosetu.com/favnovelmain/list/") do |favorite_top_page|
    favorites = favorite_top_page.search("ul.category_box li a").map do |category_link|
      [category_link.inner_text.sub(/\(\d+\)/,""),category_link.get_attribute(:href)]
    end

    favorite_category_ncodes = {}
    favorites.each do |tag, link|
      favorite_category_ncodes[tag] = get_ncode_all_from_favorite_page(agent,link)
    end
    return favorite_category_ncodes
  end
end

#ログイン
def narou_login()
  agent = Mechanize.new
  agent.get("https://ssl.syosetu.com/login/input/") do |login_page|
    login_page.form_with(:action => '/login/login/')  do |form|
      form.field_with(:name => 'id').value = USER_DATA["mail"]
      form.field_with(:name => 'pass').value = USER_DATA["password"]
    end.click_button
    yield(agent)
  end
end


def delete_all_favorite_tag(file,favorite_category_ncodes)
  favorite_category_tags_string = favorite_category_ncodes.keys.join(" ")
  file.puts("for i in do `seq 1 100`; do ")
  file.puts("narou tag --delete '#{favorite_category_tags_string}' $i")
  file.puts("done;")
end



narou_login do |agent|
  favorite_category_ncodes = get_favorite_ncodes(agent)
  File.open("temp.bash","w") do |file|
    file.puts("narou s update.interval=3.0")
    file.puts("narou s download.interval=1.0")
    file.puts("narou s download.wait-steps=5")
    delete_all_favorite_tag(file,favorite_category_ncodes)
    favorite_category_ncodes.each do |new_fav_category_tag, ncode_list|
        file.puts("narou download  #{ncode_list.join(" ")}")
        file.puts("narou tag --add '#{new_fav_category_tag}'  #{ncode_list.join(" ")}")
    end

  end
end

