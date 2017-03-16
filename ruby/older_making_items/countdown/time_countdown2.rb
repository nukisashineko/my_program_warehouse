#!/bin/sh
exec ruby -x "$0" "$@"
#!ruby
# -*- coding : utf-8 -*-

require 'time'

def this_is_OK?(string)
 input=nil
 until(input=="y" or input=="n")
 puts string+"?\t[y/n]"
  input=gets().chomp 
end
 return true if input=="y"
 return false if input=="n"
 return "error"
end

def to_cvs(*arg)
 temp=arg.shift.to_s if arg!=[]
 until arg==[]
  temp<<" "
  temp<<arg.shift.to_s
 end
 return temp
end


#enum,どれくらいの頻度で繰り返すのか？もしくは残り時間
module ScheduleType
 DAY=1
 WEEK=2
 MONTH=3
 YEAR=4
 LIMIT=5
end

module Second
 MONTH=24*60*60*30
 DAY=24*60*60
 HOUR=60*60
 MINUTE=60
end

class Schedule
 @start_time=@end_time=Time.new
 @name=String.new
 
 attr_reader :type,:name,:end_time,:start_time

 def initialize(type,name,time_start,time_end)
 @type=type
 @name=name
 @time_start=time_start
 @time_end=time_end
 end

 def during(a=@time_end,b=@time_start)
  during=(b-a).abs
  case str
  when "year" then return during.divmod(Second::DAY*365)
  when "month" then return during.divmod(Second::DAY*30)
  when "week" then return during.divmod(Second::DAY*7)
  when "day" then return during.divmod(Second::DAY)
  when "hour" then return during.divmod(Second::HOUR)
  when "min" then return during.divmod(Second::MINUTE)
  when "second" then return during.divmod(1)
  else print "func during  arg only 'day','hour','min' or 'second' !!";exit
  end
 end
 
 def dates_overlap?(other,after_start=0)
   start_time=@start_time+after_start
   end_time=@end_time
   if other.end_time<start_time and end_time<other.start_time
    return false
   else
    return true
 end
end

def readschedule(filename,schedulelist=[])
  File.readlines(filename){|line|
    type,name,start_unix_time,end_unix_time=line.split(' ')
    schedulelist.push Schedule.new(type,name,Time.at(start_unix_time),Time.at(end_unix_time))
  }
end

def writeschedule(filename,schedulelist=[])
  schedule=schedulelist.pop
  until schedule==nil
   File.open(filename,"w"){|f|
    type=schedule.type
    name=schedule.name
    start_unix_time=schedule.start_time.to_i
    end_unix_time=schedule.end_time.to_i
    f.puts to_cvs(type,name,end_unix_time,start_unix_time) 
   }
  end
end

def type_search(schedulelist,type)
  return schedulelist.select{|i| i.type == type }
end

def dates_overlap_array(one,others)
 return others.select{|other| one.dates_overlap?(other)}
end

def func_day(limit)
   i=1
   temp=limit.start_time
   old_month=temp.month
   old_year=temp.year
   while( limit.during("day")[0]>Second::DAY*i )
     sum+=months(start) if  old_month!=temp.month 
     sum+=year 
     less
    temp+=Second::DAY 
    old_month=temp.month
    old_year=temp.year
    i+=1
   end
   if dates_overlap?
    sum+=during
end


def printlimit(schedulelist)
  
  days=type_search(schedulelist,ScheduleType::DAY)
  weeks=type_search(schedulelist,ScheduleType::WEEK)
  months=type_search(schedulelist,ScheduleType::MONTH)
  years=type_search(schedulelist,ScheduleType::YAER)
  limits=type_search(schedulelist,ScheduleType::LIMIT)
  
  limits.each do |limit|
   temp=limit
   limit.start_time+  
 
  hour,temp=remaining_time.divmod(Second::HOUR)
  min=temp.div(Second::MINUTE)
  puts name+"まで\t残り"+hour+"時間"+min+"分"

end


p temp=Schedule.new("test 60",Time.now,Time.now+60)
p temp.during("second")


printline="aaaa"
filename="temp.file"

File.open(filename,"a"){|f| f.puts printline}


