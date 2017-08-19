rem ***
rem *** our WebRTC server can not accept port in the white list entry. And Chrome attaches port in
rem *** HTTP request header if port is a non-standard one !
rem ***
rem *** http-server ./webrtc-sample -d -p 8443 -S -C c:/BIN/cert/cert.pem -K c:/BIN/cert/key.pem
rem ***
rem *** use -c-1 to disable server side caching
rem ***
rem *** default port is 8080 !
rem ***
http-server ./www -c-1 -d

