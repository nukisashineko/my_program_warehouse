

class OpenStreetMapTile
  attr_reader :longitude, :latitude, :xtile, :ytile
  def initialize(longitude: nil, latitude:nil, xtile: nil, ytile: nil)
    raise "Arguments Error" until (longitude && latitude) || (xtile && ytile)

  end

  def calc_x_y_from_lng_lat(zoom, lon_deg, lat_deg)
    lat_rad = ( lat_deg * Math::PI/ 180.0 )
    n = 2 ^ zoom
    xtile = n * ((lon_deg + 180) / 360)
    ytile = n * (1 - (Math.log(Math.tan(lat_rad) + 1/Math.cos(lat_rad)) / π)) / 2
    [xtile, ytile]
  end

  def calc_lng_lat_from_x_y(zoom, xtile , ytile )
    n = 2 ^ zoom
    lon_deg = xtile / n * 360.0 - 180.0
    lat_rad = Math.atan(Math.sinh(Math.PI * (1 - 2 * ytile / n)))
    lat_deg = lat_rad * 180.0 / Math.PI
    [lon_deg,lat_deg]
  end
end
