---
# Table of Contents
- [Download & Setup for Windows](#download--setup-for-windows)
  - [Install & Setup MinGW Compiler:](#install--setup-mingw-compiler)
  - [Install & Stepup Visual Studio Code:](#install--stepup-visual-studio-code)
- [Download & Setup for Mac](#download--setup-for-mac)
  - [Install & Setup for VSCode + Clang](#install--setup-for-vscode--clang)

---
# Download & Setup for Windows
## Install & Setup MinGW Compiler:
1. Go to this website [MinGW from SorceForge](https://sourceforge.net/projects/mingw/) and download MinGW
2. Run the downloaded setup and press install
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001348.png)

4. Change installation directory if you want, check "…for all users * …" box if you want. Press continue
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001435.png)

5. When the installation is completed, press continue, and MinGW Installation Manager will open
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001513.png)

6. Right-click on each entry under the Package heading and click "Mark for Installation"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001617.png)

7. Press "Installation" on the top left and click on "Apply Changes"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001649.png)

8. A window will open, press "Apply" again
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001710.png)

9. After the installation is complete press "Close". If on pressing "Close" the setup says that packages will be discarded then do step 6 again because some files were not downloaded
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001734.png)

10. Go to the directory where you installed MinGW and open "bin" folder
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001836.png)

11. Now click on the top bar in the folder (Anywhere after bin)
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001900.png)

12. Now copy the directory path
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001930.png)

13. Search "Environment variables" and open "Edit the system environment variables"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323001958.png)

14. A window will open, click on "Environment Variables"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323002022.png)

15. Another window will open. On this window under the "System Variables", select "Path" and then press "Edit"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323002058.png)

16. Another window will open. Click new and paste the copied directory and press "Ok"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323002136.png)

17. Now search cmd and open Command Prompt
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323002204.png)

18. Now to test if MinGW compiler was successfully installed type "gcc -v" without the quotation marks in Command Prompt and press enter. If you see "gcc is not recognized as an internal or external command" as the output, then you have done something wrong while setting up the environment variable
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323002248.png)

---
## Install & Stepup Visual Studio Code:
1. Go to [Visual Studio Code Official Webpage](https://code.visualstudio.com/download) and download for windows then open the downloaded setup
2. Accept the agreement and press "Next"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323002617.png)

3. Select the directory where you want to install and press "Next"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323002846.png)

4. Again press "Next"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323002941.png)

5. Now check all the boxes MOST IMPORTANTLY the "Add to Path" box and press "Next".
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323003011.png)

6. Now press "Install"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323003033.png)

7. After the installation is complete check "Launch Visual Studio Code" box and click on "Finish"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323003056.png)

8. VSCode will open, now click on "Extensions" in the left bar. Search "C++" and click on the first search result and press "Install"
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323003154.png)

---
# Download & Setup for Mac
## Install & Setup for VSCode + Clang
1. Go to [VSCode Official Site](https://code.visualstudio.com/download) and download for Mac then open the downloaded setup. It's a 169MB file so might take few minutes to download. Patience is the key!
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323003554.png)

2. Drag the zip from downloads to Desktop. Double click on it. Double click on the VS Code's icon and click open.
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323003651.png)

3. VS Code will open, now click on "Extensions" in the left bar. Search "C++" and click on the first search result (C/C++ by Microsoft) and press "Install"
4. Search "Code Runner" and click on the first search result (Code Runner by Jun Han) and press "Install"
5. Now to open the terminal.
6. Clang may already be installed on your Mac. To verify that it is, open a macOS Terminal window and enter the following command: 'clang –version
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323003914.png)

7. If Clang isn't installed, enter the following command on terminal: `xcode-select --install`
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323004022.png)

8. After you give it the command it should show a Popup. Press install
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323004053.png)

9. Agree to terms and conditions:
![Name](../Attachments/Cpp_Setup_Manual/Pasted%20image%2020260323004202.png)

---
