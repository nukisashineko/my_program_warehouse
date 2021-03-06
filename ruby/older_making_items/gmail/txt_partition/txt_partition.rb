#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-


class MyOutput
  def initialize ( name ,open_type )
    @name =name
    @count = 0
    @sum = 0
    @filename = sprintf("%s_%03d.txt",@name,@count)
    @open_type = open_type
    @file = self.file_open
    @code = "SJIS"
    @canUseSize = 10*2**10 #10Kbite
  end
  def write(sentence)
    if(@canUseSize <= @sum + sentence.bytesize)
      self.next
      @sum=0
    end
    @file.write sentence
    @sum+=sentence.bytesize
  end
  def read()
    str = nil
    str = @file.read() if(@file)
    return str
  end
  def next
    @file.close
    @count+=1
    @filename = sprintf("%s_%03d.txt",@name,@count)
    @file = self.file_open
  end
  def file_open()
      f = nil
    if(@open_type ==  "r")
      f = File.open(@filename,"r") if(File.exists?(@filename))
    else
      f = File.open(@filename,@open_type)
    end
    return f
  end
  def close
    @file.close
  end
end


def txt_partition (filename)
  pwd = Dir::pwd
 unless File.directory?(pwd+"/#{filename}")
  puts "do mkdir "
    Dir::mkdir(pwd+"/#{filename}")
 end
  Dir::chdir(pwd+"/#{filename}")
  `cp ../#{filename}.txt #{filename}.txt`
  output = MyOutput.new(filename,"w")
  File.open(filename+".txt").each_line do |line|
   line.each_line(".") do |sentence|
      output.write sentence
    end
  end
  output.close
  `rm #{filename}.txt`
  Dir::chdir(pwd)
end

def rm_txt_partition(file_name)
   pwd = Dir::pwd
  unless File.directory?(pwd+"/#{filename}")
    return "#{file_name} directory is not exists !!"
  end
  Dir::chdir(pwd+"/#{filename}")
  input = MyOutput.new(filenamie,"w")
  output.close
  `rm #{filename}.txt`
  Dir::chdir(pwd)
end


def main
if ARGV.length ==0
  puts "Usage: #{$0} <filename> [filename]..."
else
  for x in ARGV
    if File.file?(Dir::pwd+"/#{x}.txt")
      print "#{x}.txt is exists. wait a mimute.... "
      txt_partition(x)
      puts "done."
    else
      puts "#{x}.txt is not exists."
    end
  end
end
end

