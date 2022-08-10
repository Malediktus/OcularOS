if [ $1 -eq 0 ]
then
    sudo dd if=../kernel/bin/os.bin of=/dev/disk2 bs=`ls -nl ../kernel/bin/os.bin | awk '{print $5}'` count=1
fi

if [ $1 -eq 1 ]
then
    sudo dd if=/dev/disk2 of=../kernel/bin/os.bin bs=`ls -nl ../kernel/bin/os.bin | awk '{print $5}'` count=1
fi