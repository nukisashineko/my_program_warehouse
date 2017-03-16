#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-
class Duration
	def initialize(since, till)
			@since = since
			@until = till
	end
	attr_accessor :since, :until
#	attr_reader :since :until
#	attr_writer :since :until
end

duration = Duration.new(Time.now,Time.now + 3600)
p duration.until
p duration.since= Time.now

