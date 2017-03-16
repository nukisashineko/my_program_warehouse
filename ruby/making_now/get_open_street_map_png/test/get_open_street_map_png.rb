require_relative "../get_open_street_map_png"
require "test-unit"



class TestSample < Test::Unit::TestCase
  # 'test1'がラベルで，[1, 1]がtest_equalの引数に渡される
  data(
      'test1' => [1, 1],
      'test2' => [2, 2])
  def test_equal(data)
    expected, actual = data
    assert_equal(expected, actual)
  end

  data(
      'test1' => [1, 2],
      'test2' => [2, 3])
  def test_not_equal(data)
    expected, actual = data
    assert_not_equal(expected, actual)
  end
end