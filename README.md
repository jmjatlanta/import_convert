This is a simple program that reads the file exported from Interactive Brokers' Trader Workstation and creates a file that can be accepted by [TraderVue.com](http://www.tradervue.com).

# Building the application
You must have CMake and your C++ compiler properly installed for your platform. This has been tested on Linux, but should work for Mac, and probably Windows (Visual C++ or others that CMake supports).

For Linux and Mac, the command `cmake` should build the required Makefiles. Then `make` should build the application

# Exporting the file from Trader Workstation
Select **Account -> Trade Log** for your trade log window to appear. Then choose **File -> Export Today's Reports...**. Select the **Extended Form** radio button, note the Filename so you know where it will put the file (you can change it there too), and click the **OK** button.

# Using the application
From the command line (i.e. the Terminal application) type

`import_convert in_filename.csv out_filename.csv`

whereby `in_filename.csv` is the name of the file that was exported from Interactive Brokers, and `out_filename.csv` is the name of the file that will be created, which you can then use to import the data into TraderVue.

The files can be in different directories. For an example, if the file from Interactive Brokers was in the Documents directory, which was a subdirectory of where you are, you can type `import_convert ./Documents/in_filename.csv out_filename.csv` and it will work as expected.

# Notes
* I use an IB Advisor account. But I do not think that should affect anything. If you are also using an Advisor account, you may wish to only export the sub-accounts you want displayed in TraderVue. This program is not smart enough to separate different accounts into separate files.
* I do not use the TraderVue Gold account. Commissions are included in the export, but untested.

This code is released under the MIT license. See [LICENSE](https://github.com/jmjatlanta/import_convert/blob/master/LICENSE) for details.