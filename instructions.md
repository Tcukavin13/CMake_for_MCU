Устанавливаем ARM toolchain:<br>
```$ sudo apt install gcc-arm-none-eabi```<br> 
```$ sudo apt install binutils-arm-none-eabi```<br>
<br>
Устанавливаем отладчик GDB:<br>
```$ sudo apt install gdb-multiarch```<br>
<br>
Чтобы иметь возможность выполнять команду ```arm-none-eabi-gdb``` после установки **gdb-multiarch** необходимо добавить следующую символическую ссылку:<br>
```ln -s /usr/bin/gdb-multiarch /usr/bin/arm-none-eabi-gdb```<br>
<br>
Устанавливаем OpenOCD.<br>
Скачиваем с оффициального сайта архив с пакетом ArteryIDE и копируем оттуда папку OpenOCD в произвольное место на файловую систему. Затем, чтобы OpenOCD можно было запускать из произвольного места короткой командой ```openocd```, добавляем символическую ссылку в каталог поиска программ - ```/usr/bin```:<br>
```sudo ln -s /home/tcukavin13/OpenOCD/bin/openocd /usr/bin/```<br>
<br>
В **launch.json** прописываем пути поиска зависимостей пакета openocd:<br>
 ```"searchDir": [ "/home/tcukavin13/OpenOCD/scripts" ]```<br>
 <br>
В качестве генератора CMake в файле **CMakePresets.json** задаём ```Unix Makefiles```:<br> 
```"generator": "Unix Makefiles"```