cd Desktop/SharedFolders
ls
cd sf_Z_DRIVE/
ls
cd ..
rm -Rf sf_Z_DRIVE/
sudo rm -Rf sf_Z_DRIVE/
ls
cd
cat /dev/zero > zero.fill; sync; sleep 1; sync; rm -f zero.fill
df
df -h
