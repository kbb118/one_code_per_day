#!/usr/bin/env ruby
require 'uri'

project = 'kbbkbb524' # 自分のプロジェクト名
title = Time.now.strftime('%Y-%m-%dT%H:%M')

body = <<EOS
[#{Time.now.strftime('%Y/%-m')}]
[** ライフログ]
	起床
		    
	朝食
		
	昼食
		
	夕食
		
	就寝
		
EOS

body = URI.encode(body)
system "vivaldi https://scrapbox.io/#{project}/#{title}?body=#{body}"
