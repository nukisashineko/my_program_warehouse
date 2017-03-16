def error(str)
 p str
 exit
end
def get_user_history(name)
 #cd  user's date spece
  error("file not exits.") unless File.exist?(name)
  user_history = open(name).readline
  len = user_history.lenght
  #history size until 50 lines
  if (len>50) then
  open(name,"w"){|file|
  for x in user_history[len-50...len]
   file.puts(x)
  end
  }
  user_history = user_history[len-50...len]
  end
  return user_history
end


def after_contact(name,subject,body,url)
  new_user_date(name) unless exist_user(name)
  user_log_write(name,subject,body)
  user_history_write(url)
  user
end

