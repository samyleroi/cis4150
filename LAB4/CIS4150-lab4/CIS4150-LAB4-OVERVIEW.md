
Overview
========

The purpose of this lab is to build our skills using a commercial
testing environment in the context of model based testing.

We will use a Java version of the "`gpalib`" library that we have
looked at over the last few weeks, now called `GPAconverter`


The problem at hand
-------------------

In the last lab, we examined the `gpalib` library in C, and did
simple evaluation of calculation.

This week we will update our test case strategy to examine setting
up test cases in JUnit.

JUnit version 4 documentation can be found at this website:
[http://junit.org/junit4/](http://junit.org/junit4/)

To define a particular test case, code such as the following is used:

	@Test
	public void test100percent()
	{
		String got, need = "A+";
		got = GPAconverter.getLetterForNumericGrade(100);
		assertEquals(need, got);
	}

A method decorated with `@Test` is flagged for use as a test case,
when run within a JUnit test suite evaluation strategy.  Such a
strategy, assuming that the above code is compiled into a class
file "`TestCases.class`" would look like this:

	/** overall result of this test run */
	Result result = JUnitCore.runClasses(TestCases.class);

	System.out.format("Overall conversion result was : %s\n",
			result.wasSuccessful() ? "SUCCESS" : "FAILURE");

	if ( ! result.wasSuccessful()) {
		System.out.format("List of conversion test failure messages:\n");
		for (Failure failure : result.getFailures()) {
			System.out.println(failure.toString());
		}
	}

The JUnit tests are based around calls to some variant of the JUnit
`assert` methods, as detailed here:
[http://junit.org/junit4/javadoc/4.12/org/junit/Assert.html](http://junit.org/junit4/javadoc/4.12/org/junit/Assert.html)

Each call to a JUnit `assert` method within a `@Test` decorated method
will evaluate a single test.  Multiple `assert` calls can exist within
the same method.


### Code to test

A starting framework for JUnit testing, as well as a Java implementation
of the `GPAconverter` code is provided
[in this .zip file](http://skeeter.socs.uoguelph.ca/~andrew/teaching/cis4150/CIS4150-lab4.zip).

Javadoc class documentation for the Java implementation of `GPAconverter` 
[is also provided](http://skeeter.socs.uoguelph.ca/~andrew/teaching/cis4150/GPAcalculator-classdocs/).


### Tests to generate

This week, we wish to explore two things:

* simple test cases
* test cases involving some type of model


You can see a simple test case implemented for you in `TestConversions.java`.  You
can build and run this test using the instructions in `buildAndRunAllTestCases`,
which are reproduced here:

	javac -cp GPAcalculator.jar:junit-4.10.jar:. \
			RunAllTests.java TestConversions.java TestWithModel.java
	java -cp GPAcalculator.jar:junit-4.10.jar:.  RunAllTests


Note that the `-cp` flag sets the `CLASSPATH` variable.  It is important to
add both the jar file containing the GPA calculator as well as the JUnit
tools to the class path, as these are not installed by default.  The dot
at the end of the CLASSPATH ensures that files in the local directory are
still read.  Note that every `.java` file needs to be compiled independently,
as due to the direct loading of the test classes, there is no implicit
dependency detectable to Java.


Model based work will require setting up a model before running our test
cases, and then using it in each case.  To do this, we use the JUnit technology
called a "Fixture", which is described here:
[https://github.com/junit-team/junit4/wiki/Test-fixtures](https://github.com/junit-team/junit4/wiki/Test-fixtures).



Your Tasks
==========

We wish to build a simple model to act as an "oracle" for our system,
and then use this model in our code.

Task 1: design your model
-------------------------

We wish to design a model to further understand the code we examined
last week based on GPA calculations:

* `float GPAcalculator.GPAcalculator.getTermGPA(String term)`

	A method that will return the average of the term GPA calculation.

* `float GPAcalculator.GPAcalculator.getOverallGPA()`

	A method that will return the average of all GPA calculations.


Note that in both of these functions, we are trying assess whether
the average is calculated properly.

Your task is to assess how to develop a model that can give you an
answer regarding the proper GPA average, which you can compare with
this function.

*Hint:* you may, if you wish, use simpler functions from the `GPAconversion`
class.


Write a short description of your approach into a file entitled
LAB4-DESIGN
(you can give this the extension `.txt` or `.md` if you wish).


Task 2: simple JUnit implementation
-----------------------------------

Add at least six more test cases to the `TestConversions.java` class.

Explain what strategy you are using to decide upon which test cases
to choose, based on the strategies we have discussed in class.  Add
your explanation to the LAB4-DESIGN file.


Task 3: model based JUnit implementation
----------------------------------------

Extend your testing by implementing further test cases in the
`TestWithModel.java` file.  Be sure to create your model before
your test cases run.

Explain what strategy you are using here in order to evaluate
whether the term and overall GPA are being calculated correctly.

Task 4:
-------

**DEMONSTRATE YOUR WORK** to one of your instructors.
Be sure to demonstrate at least a partial answer by the end of the lab period.

Task 5:
-------

**HAND IN YOUR WORK** by uploading your work to CourseLink.
Please upload a single archive file, using either `.zip` or `tar`
format.  _Ensure that your archive has **all** of the following files_:

* a `README` file indicating what files you are including.  In this
  file, be sure to indicate how many test cases you have completed.
* your `LAB4-DESIGN` file.
* any and all code required to build and run your programs.

Be sure to **INDICATE YOUR LAB PAIRINGS** by setting up a "group"
for this lab in CourseLink.


Bonus:
------

If you have demonstrated and handed in an archive before the end
of the lab, you can hand in an updated archive within 24 hours
of the end of the lab.  The updated archive will be used to
calculate your lab grade.

