@echo off

if exist scripts\ (
   pushd "scripts"
)

python -m pip install --upgrade pip
python -m pip install -r requirements.txt
python setup.py

popd
PAUSE