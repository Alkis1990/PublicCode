kill -9 `ps x | grep alkis | cut -d" " -f2`
unlink jms_in
unlink jms_out
rm rcv*
rm snd*
rm -rf temp
ls -l
