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
[*** ライフログ] ([毎日ライフログを取る] )
	[** 起床]
		
	[** 朝食]
		
	[** 昼食]
		
	[** 昼休み] ([毎日昼休みに散歩する] )
		
	[** 夕食]
		
	[** 体重] ([毎日体重を計る] )
		
	[** 就寝]
		

[*** ランニング] ([毎日3.3km走る] )
	

[*** 英単語] ([毎日5語新しい英単語(熟語)を覚える] )
	
	
	
	
	

[*** コード] ([毎日Githubにコードを公開する] )
	

[*** 日記] ([毎日日記を書く] )
	確認項目 [毎日一日の作業を見積もってから始業する] 

EOS

body = URI.encode(body)
# () が sh に解釈されないように。
body = URI.escape(body, "()")
system "vivaldi https://scrapbox.io/#{project}/#{title}?body=#{body}"
