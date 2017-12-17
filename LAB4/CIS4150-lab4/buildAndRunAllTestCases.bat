REM build and run our test set
@echo on

javac -cp GPAcalculator.jar:junit-4.10.jar:. RunAllTests.java TestConversions.java TestWithModel.java
java -cp GPAcalculator.jar:junit-4.10.jar:. RunAllTests

