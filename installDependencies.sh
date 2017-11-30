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
sudo apt-get install xorg
echo ""

echo "+-------------------+"
echo "| Installing python |"
echo "+-------------------+"
sudo apt-get install python
echo ""

echo "+-----------------+"
echo "| Installing glad |"
echo "+-----------------+"
sudo -H pip install glad
cd build
python -m glad --generator c --no-loader --out-path gladbuild 
cd .. 
