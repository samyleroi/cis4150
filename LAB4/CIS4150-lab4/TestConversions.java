import org.junit.Test;
import static org.junit.Assert.assertEquals;

import GPAcalculator.*;

public class TestConversions
{
	@Test
	public void test100percent()
	{
		String got, need = "A+";
		got = GPAconverter.getLetterForNumericGrade(100);
		assertEquals(need, got);
	}

	@Test
	public void test99percent()
	{
		String got, need = "A+";
		got = GPAconverter.getLetterForNumericGrade(99);
		assertEquals(need, got);
	}
	
    @Test
	public void test50percent()
	{
		String got, need = "D-";
		got = GPAconverter.getLetterForNumericGrade(50);
		assertEquals(need, got);
	}

	@Test
	public void test0percent()
	{
		String got, need = "F";
		got = GPAconverter.getLetterForNumericGrade(0);
		assertEquals(need, got);
	}
    
	@Test
	public void test49percent()
	{
		String got, need = "F";
		got = GPAconverter.getLetterForNumericGrade(49);
		assertEquals(need, got);
	}

	@Test
	public void test51percent()
	{
		String got, need = "D-";
		got = GPAconverter.getLetterForNumericGrade(51);
		assertEquals(need, got);
	}

	@Test
	public void test90percent()
	{
		String got, need = "A+";
		got = GPAconverter.getLetterForNumericGrade(90);
		assertEquals(need, got);
	}

	@Test
	public void test89percent()
	{
		String got, need = "A";
		got = GPAconverter.getLetterForNumericGrade(89);
		assertEquals(need, got);
	}

	@Test
	public void testAPlusGPA()
	{
		double got, need = 4.3;
		got = GPAconverter.getGPAforLetterGrade("A+");
		assertEquals(need, got, 0.000001);
	}

	@Test
	public void testFGPA()
	{
		double got, need = 0.0;
		got = GPAconverter.getGPAforLetterGrade("F");
		assertEquals(need, got, 0.000001);
	}

	@Test
	public void testCGPA()
	{
		double got, need = 2.0;
		got = GPAconverter.getGPAforLetterGrade("C");
		assertEquals(need, got, 0.000001);
	}

	@Test
	public void test80GPA()
	{
		double got, need = 3.7;
		got = GPAconverter.getGPAforNumericGrade(80);
		assertEquals(need, got, 0.000001);
	}
	
    @Test
	public void test79GPA()
	{
		double got, need = 3.3;
		got = GPAconverter.getGPAforNumericGrade(79);
		assertEquals(need, got, 0.000001);
	}

    @Test
	public void test72GPA()
	{
		double got, need = 2.7;
		got = GPAconverter.getGPAforNumericGrade(72);
		assertEquals(need, got, 0.000001);
	}
}
