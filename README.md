# UI_Pangolin

environment:
ubuntu16.04 ROS kinetic 

UI interface made by **leo lu**
![waka-UI](https://github.com/mocapNCTU/UI_Pangolin/blob/master/external/waka-UI.png)

Installation 
========
***Preinstall:***
`sudo apt-get install libglm-dev`

Building
========

```bash=
git clone https://github.com/mocapNCTU/UI_Pangolin.git

cd ~/UI_Pangolin 
mkdir build 
cd build 
cmake ..
make PangolinROSUI 
cd ~/UI_Pangolin/build/examples/HelloPangolin 
./PangolinROSUI 
```
