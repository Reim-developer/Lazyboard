run

catch signal SIGSEGV
commands
	bt full
	quit
end