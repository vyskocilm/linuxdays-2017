
#build

gcc -lczmq zauth.c

# run the server

./a.out --endpoint ipc://@/zauth --server --private mycert.txt_secret --verbose

# run the client

./a.out --endpoint ipc://@/zauth --client --private mycert.txt_secret --public mycert.txt  --verbose
