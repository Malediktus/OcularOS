if [ $1 -eq 0 ]
then
    sudo dd if=./bin/os.bin of=/dev/disk2 bs=`ls -nl bin/os.bin | awk '{print $5}'` count=1
fi

if [ $1 -eq 1 ]
then
    sudo dd if=/dev/disk2 of=./bin/os.bin bs=`ls -nl bin/os.bin | awk '{print $5}'` count=1
fi