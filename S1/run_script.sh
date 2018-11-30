make clean
make
echo ""
echo "Creating one server and one client"

x-terminal-emulator -t SERVER -e ./.server.sh
sleep 2

x-terminal-emulator -t CLIENT -e ./.client.sh 
