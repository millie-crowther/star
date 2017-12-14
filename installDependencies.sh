echo "+------------------+"
echo "| Installing CMake |"
echo "+------------------+"
sudo apt install cmake
echo ""

echo "+----------------+"
echo "| Installing GLM |"
echo "+----------------+"
sudo apt-get install libglm-dev
echo ""

echo "+-----------------+"
echo "| Installing xorg |"
echo "+-----------------+"
sudo apt-get install xorg xorg-dev libglu1-mesa-dev
echo ""

echo "+-------------------+"
echo "| Installing python |"
echo "+-------------------+"
sudo apt-get install python
echo ""

echo "+----------------+"
echo "| Installing pip |"
echo "+----------------+"
sudo apt install python-pip
echo ""

echo "+-----------------+"
echo "| Installing glad |"
echo "+-----------------+"
sudo -H pip install glad
cd build
if cd gladbuild; then
    cd ..
else
    python -m glad --generator c --no-loader --out-path gladbuild 
fi
cd ..
echo ""

echo "+----------------+"
echo "| Installing X11 |"
echo "+----------------+"
sudo apt-get install libx11-dev
echo ""

echo "+-----------------+"
echo "| Installing GLFW |"
echo "+-----------------+"
if cd build/glfw; then 
    git pull
    cd ../..
else
    git clone https://github.com/glfw/glfw.git
fi
echo ""
