require "masque"
m = Masque.new(:display => 99, :driver => :webkit) # or :driver => :poltergeist
m.run do
	# Capybara::DSL syntax
	#   # https://github.com/jnicklas/capybara#the-dsl
	visit "http://www.google.com/"
	fill_in("q", :with => "capybara")
	find('*[name="btnG"]').click

	titles = evaluate_script <<-JS
						(function(){
									var titles = Array.prototype.map.call(
													document.querySelectorAll('h3 a'),
																	function(a) {
																						return a.innerText;
																										}
																													);

																																return titles;
																																		})();
	JS
	puts titles.join("\n")
end

