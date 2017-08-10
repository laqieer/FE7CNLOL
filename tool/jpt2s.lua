-- switch case 结构的跳转表汇编生成
-- usage: lua jpt2s.lua >jpt.s
-- by laqieer
-- 2017/8/11

dofile('jpt.lua')

function handler()
	s = string.format(' @ case %d\n.word\t0x',case)
	case = case + 1
	return s
end

print('.word\t0x'..string.gsub(table,'[\n ]',handler)..' @ case '..case)