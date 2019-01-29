**ATTENTION**

This example is outdated.  
Instead see:  
[https://github.com/oatpp/example-crud](https://github.com/oatpp/example-crud) 

**ATTENTION**


# example-oatpp-swagger
c++/oat++ Web Service with Swagger-UI and auto-documented endpoints

More about oatpp see [https://oatpp.io/](https://oatpp.io/)  
More about oatpp-swagger [https://github.com/oatpp/oatpp-swagger](https://github.com/oatpp/oatpp-swagger)  
More about Swagger UI see [https://swagger.io/tools/swagger-ui/](https://swagger.io/tools/swagger-ui/)

## Build and run

1) Git-Clone examples repo:
```
$ git clone --recurse-submodules https://github.com/lganzzzo/example-oatpp-swagger
```
2) CD to example-oatpp-swagger
```
cd example-oatpp-swagger/
```
3) Build project
```
./build_app.sh
```
or (same as in build_app.sh)
```
g++ -std=gnu++11 \
-pthread \
`find "./lib/oatpp/" -type f -name *.cpp` \
`find "./src/" -type f -name *.cpp` \
`find "./lib/oatpp-swagger/" -type f -name *.cpp` \
-I "./lib" \
-I "./src" \
-D OATPP_USE_TARGET \
-D OATPP_TARGET_APP \
-D OATPP_DISABLE_ENV_OBJECT_COUNTERS \
-O2 \
-Wall \
-o run_app

chmod +x run_app
```
4) Run app
```
./run_app
```

enjoy!

## More
If you can't build app.- probably you need to [install build-essential](https://www.google.com.ua/search?q=install+build-essentials)

## Xcode, MAC
Xcode project included
