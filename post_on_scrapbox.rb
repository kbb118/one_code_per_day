#!/bin/sh
exec ruby -x "$0" "$@"
#!ruby
require 'uri'

project = 'kbbkbb524' # 自分のプロジェクト名
title = Time.now.strftime('%Y-%m-%dT%H:%M')

#TODO 土日祝日は違うフォーマット
#TODO 天気予報を取得して埋め込み
body = <<EOS
[#{Time.now.strftime('%Y/%-m')}]
[*** ライフログ] ([毎日ライフログを取る] [done.icon])
	[** 起床]
		
	[** 朝食] ([毎月半分は自炊する] or [毎月3回は新しい飲食店を開拓する] [todo.icon])
		
	[** 昼食] ([毎月半分は自炊する] or [毎月3回は新しい飲食店を開拓する] [todo.icon])
		
	[** 昼休み] ([毎日昼休みに散歩する] [todo.icon])
		
	[** 夕食] ([毎月半分は自炊する] or [毎月3回は新しい飲食店を開拓する] [todo.icon])
		
	[** 体重] ([毎日体重を計る] [todo.icon])
		
	[** 就寝]
		

[*** ランニング] ([毎日3.3km走る] [todo.icon])
	

[*** 英単語] ([毎日5語新しい英単語(熟語)を覚える] [todo.icon])
	
	
	
	
	

[*** コード] ([毎日Githubにコードを公開する] [todo.icon])
	

[*** 日記] ([毎日日記を書く] [todo.icon])
	確認項目 [毎日一日の作業を見積もってから始業する] [todo.icon]

EOS

body = URI.encode(body)
# () が sh に解釈されないように。
body = URI.escape(body, "()")
system "vivaldi https://scrapbox.io/#{project}/#{title}?body=#{body}"
