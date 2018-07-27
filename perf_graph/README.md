### Run
```sh
python app.py
```
### Route

route | description
---- | ----
 '/'        |io rate compare of spark,c++,standard
 '/pressure/spark/[iorate]' |pressure result of spark
'/pressure/c++/[iops,iorate]' |presssure result of c+=

首页可以直接这样
wget -c -r -np -k -L -p http://0.0.0.0:5000


其他页面下载后的内容需要rename加下.html 后缀就好。
wget -c -r -np -k -L -p http://0.0.0.0:5000/pressure/c++/iorate   


