
require 'csv'

csvdata = CSV.read('worklog.csv',headers: true )
# row = csvdata[0]

#日毎に集計をまとめる
summarys = {}
csvdata.each do |row|
	starttime = DateTime.parse("#{row['date']} #{row['starttime']} +09:00").to_time
	endtime = DateTime.parse("#{row['date']} #{row['endtime']} +09:00").to_time
#	p row['date']
#	p summarys[row['date']] ? "Object": nil
	summarys[row['date']] ||= {tasks: [], sumtime: 0,starttime:starttime,endtime:starttime}
	summarys[row['date']][:tasks].push row['taskname'] 
	summarys[row['date']][:sumtime] += (endtime - starttime)
	#時間のつじつま合わせ。同日内になるように時間を調整する。
	if( (summarys[row['date']][:endtime] + (endtime - starttime)).strftime('%d') == starttime.strftime('%d') )
		summarys[row['date']][:endtime] +=  (endtime - starttime)
	else
		summarys[row['date']][:starttime]  -=  (endtime - starttime)
	end
#	p summarys[row['date']]
end
#p summarys

# 集計した時間を元に書き出すために少し整形する。（一時間単位に変更する。繰り上げた分によって）
fraction_minutes = 0
results = {}
summarys.keys.sort{|a,b| Date.parse(a) <=> Date.parse(b)}.each do |date|
	row = summarys[date]
	worktime = {hour:row[:sumtime].div(3600) ,minutes:row[:sumtime].div(60)%60}
	month = Date.parse(date).strftime("%m月")
	taskname = row[:tasks].join(' ')

	#デバック用
#	jatime = "#{worktime[:hour]}時間 #{worktime[:minutes]}分"
#	puts "#{taskname[0..30]} #{jatime}"

	#main 
	results[month] ||= []
	fraction_minutes += worktime[:minutes]
#	puts "fraction_minutes = #{fraction_minutes}"
	results[month].push({date: Date.parse(date).strftime('%d'),start:row[:starttime], end:row[:endtime],taskname: taskname, workhour: worktime[:hour] + fraction_minutes.div(30)*1.0/2 })
	fraction_minutes %= 30
puts " #{fraction_minutes}分"
end
puts "次の月への繰越の分は #{fraction_minutes}分です"

#データの書き出し。
File.open('reformat_worklog.csv','w') do |f|
	results.each do |month, array|
		array.each do |row|
			f.puts [
				month,
				row[:date],
				row[:start].strftime('%l:%M:00 %p'),
				row[:end].strftime('%l:%M:00 %p'),
				row[:workhour], 
				row[:taskname][0..30]
			].join(',')
		end
	end
end


