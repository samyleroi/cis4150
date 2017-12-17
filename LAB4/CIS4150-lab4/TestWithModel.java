import java.io.Closeable;
import java.io.IOException;
import java.util.*;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

import GPAcalculator.*;

public class TestWithModel
{
	private static int[] testNumericNorm = { 100, 0, 50 };
	private static int[] testNumericHigh = { 91, 90, 89 };
	private static int[] testNumericLow = { 60, 41, 49 };
	private static String[] testLetterNorm = { "A+", "D-", "F" };
	private static String[] testLetterHigh = { "A+", "A", "A-" };
	private static String[] testLetterLow = { "C+", "C", "C-" };
	private static MyDataModel theModel = null;
	private static GPAcalculator testCalculator = null;

	@BeforeClass
	public static void setUpClass()
	{
		/*System.out.println("@BeforeClass setUpClass");*/
	}

	@AfterClass
	public static void tearDownClass() throws IOException {
		/*System.out.println("@AfterClass tearDownClass");*/
	}

	private void println(String string) {
		System.out.println(string);
	}

	@Before
	public void setUp()
	{
		/*this.println("@Before setUp");*/
	}

	@After
	public void tearDown() throws IOException
	{
		/*this.println("@After tearDown");*/
	}

	@Test
	public void test0()
	{
		/*this.println("@Test in test");*/
	}

	@Test
	public void testLowOverallGPANumeric()
	{
		double got, need;
        this.theModel = new MyDataModel();
        this.testCalculator = new GPAcalculator("test", "0123");
        testCalculator.addNumericGrade("w", testNumericLow[0]);
        testCalculator.addNumericGrade("w", testNumericLow[1]);
        testCalculator.addNumericGrade("w", testNumericLow[2]);
        theModel.addNumericGrade("w", testNumericLow[0]);
        theModel.addNumericGrade("w", testNumericLow[1]);
        theModel.addNumericGrade("w", testNumericLow[2]);
		got = testCalculator.getOverallGPA();
        need = theModel.getOverallGPA();
		assertEquals(need, got, 0.00001);
	}
	
    @Test
	public void testHighOverallGPANumeric()
	{
		double got, need;
        this.theModel = new MyDataModel();
        this.testCalculator = new GPAcalculator("test", "0123");
        testCalculator.addNumericGrade("s", testNumericHigh[0]);
        testCalculator.addNumericGrade("s", testNumericHigh[1]);
        testCalculator.addNumericGrade("s", testNumericHigh[2]);
        theModel.addNumericGrade("s", testNumericHigh[0]);
        theModel.addNumericGrade("s", testNumericHigh[1]);
        theModel.addNumericGrade("s", testNumericHigh[2]);
		got = testCalculator.getOverallGPA();
        need = theModel.getOverallGPA();
		assertEquals(need, got, 0.00001);
    }
    
    @Test
	public void testHighOverallGPALetter()
	{
        double got, need;
        this.theModel = new MyDataModel();
        this.testCalculator = new GPAcalculator("test", "0123");
        testCalculator.addLetterGrade("s", testLetterHigh[0]);
        testCalculator.addLetterGrade("s", testLetterHigh[1]);
        testCalculator.addLetterGrade("s", testLetterHigh[2]);
        theModel.addLetterGrade("s", testLetterHigh[0]);
        theModel.addLetterGrade("s", testLetterHigh[1]);
        theModel.addLetterGrade("s", testLetterHigh[2]);
		got = testCalculator.getOverallGPA();
		need = testCalculator.getOverallGPA();
		assertEquals(need, got, 0.00001);
    }
    
    @Test
	public void testLowOverallGPALetter()
	{
        double got, need;
        this.theModel = new MyDataModel();
        this.testCalculator = new GPAcalculator("test", "0123");
        testCalculator.addLetterGrade("w", testLetterLow[0]);
        testCalculator.addLetterGrade("w", testLetterLow[1]);
        testCalculator.addLetterGrade("w", testLetterLow[2]);
        theModel.addLetterGrade("w", testLetterLow[0]);
        theModel.addLetterGrade("w", testLetterLow[1]);
        theModel.addLetterGrade("w", testLetterLow[2]);
		got = testCalculator.getOverallGPA();
		need = testCalculator.getOverallGPA();
		assertEquals(need, got, 0.00001);
    }
    
    @Test
	public void testLowTermGPA()
	{
        double got, need;
		got = testCalculator.getTermGPA("w");
		need = testCalculator.getTermGPA("w");
		assertEquals(need, got, 0.00001);
    }

    @Test
	public void testHighTermGPA()
	{
        double got, need;
		got = testCalculator.getTermGPA("s");
		need = testCalculator.getTermGPA("s");
		assertEquals(need, got, 0.00001);
    }
}

class MyDataModel
{
	private double sum = 0;
	private int nCourses = 0;
    private ArrayList<Double> gpas = new ArrayList<Double>();
    private ArrayList<String> terms = new ArrayList<String>();

    public MyDataModel()
    {
        sum = 0;
        nCourses = 0;
    }

    public double getOverallGPA()
    {
        return (sum / nCourses);
    }

    public double getTermGPA(String term)
    {
        double sumTerm = 0;
        int numTerms = 0;
        String tempTerm = "";
        
        for (int i = 0; i < this.gpas.size(); i++) 
        {
            tempTerm = this.terms.get(i);
            if (tempTerm.equals(term))
            {
                numTerms++;
                sumTerm += this.gpas.get(i);
            }    
        }
        
        return (sumTerm / numTerms);
    }

    public void addLetterGrade(String term, String letter)
    {
        this.nCourses++;
        if (letter.equals("A+"))
        {
            sum += 4.3;
            gpas.add(4.3);
            terms.add(term);
        }
        if (letter.equals("A"))
        {
            sum += 4.0;
            gpas.add(4.0);
            terms.add(term);
        }
        if (letter.equals("A-"))
        {
            sum += 3.7;
            gpas.add(3.7);
            terms.add(term);
        }
        if (letter.equals("B+"))
        {
            sum += 3.3;
            gpas.add(3.3);
            terms.add(term);
        }
        if (letter.equals("B"))
        {
            sum += 3.0;
            gpas.add(3.0);
            terms.add(term);
        }
        if (letter.equals("B-"))
        {
            sum += 2.7;
            gpas.add(2.7);
            terms.add(term);
        }
        if (letter.equals("C+"))
        {
            sum += 2.3;
            gpas.add(2.3);
            terms.add(term);
        }
        if (letter.equals("C"))
        {
            sum += 2.0;
            gpas.add(2.0);
            terms.add(term);
        }
        if (letter.equals("C-"))
        {
            sum += 1.7;
            gpas.add(1.7);
            terms.add(term);
        }
        if (letter.equals("D+"))
        {
            sum += 1.3;
            gpas.add(1.3);
            terms.add(term);
        }
        if (letter.equals("D"))
        {
            sum += 1.0;
            gpas.add(1.0);
            terms.add(term);
        }
        if (letter.equals("D-"))
        {
            sum += 0.7;
            gpas.add(0.7);
            terms.add(term);
        }
        if (letter.equals("F"))
        {
            sum += 0.0;
            gpas.add(0.0);
            terms.add(term);
        }
    }
    public void addNumericGrade(String term, int grade)
    {
        this.nCourses++;
        if (grade >= 90 && grade <= 100)
        {
            sum += 4.3;
            gpas.add(4.3);
            terms.add(term);
        }
        if (grade >= 85 && grade <= 89)
        {
            sum += 4.0;
            gpas.add(4.0);
            terms.add(term);
        }
        if (grade >= 80 && grade <= 84)
        {
            sum += 3.7;
            gpas.add(3.7);
            terms.add(term);
        }
        if (grade >= 77 && grade <= 79)
        {
            sum += 3.3;
            gpas.add(3.3);
            terms.add(term);
        }
        if (grade >= 73 && grade <= 76)
        {
            sum += 3.0;
            gpas.add(3.0);
            terms.add(term);
        }
        if (grade >= 70 && grade <= 72)
        {
            sum += 2.7;
            gpas.add(2.7);
            terms.add(term);
        }
        if (grade >= 67 && grade <= 69)
        {
            sum += 2.3;
            gpas.add(2.3);
            terms.add(term);
        }
        if (grade >= 63 && grade <= 66)
        {
            sum += 2.0;
            gpas.add(2.0);
            terms.add(term);
        }
        if (grade >= 60 && grade <= 62)
        {
            sum += 1.7;
            gpas.add(1.7);
            terms.add(term);
        }
        if (grade >= 57 && grade <= 59)
        {
            sum += 1.3;
            gpas.add(1.3);
            terms.add(term);
        }
        if (grade >= 53 && grade <= 56)
        {
            sum += 1.0;
            gpas.add(1.0);
            terms.add(term);
        }
        if (grade >= 50 && grade <= 52)
        {
            sum += 0.7;
            gpas.add(0.7);
            terms.add(term);
        }
        if (grade >= 0 && grade <= 49)
        {
            sum += 0.0;
            gpas.add(0.0);
            terms.add(term);
        }
    }
}
