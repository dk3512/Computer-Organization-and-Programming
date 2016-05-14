/**
 * CS 2110 Spring 2016 HW2
 * Part 1 - Coding with bases
 * 
 * @author Daniel Kim
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not declare any objects, other than String in select methods.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 *     String.equals()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   strdtoi.
 * - You may declare exactly one String variable each in itostrb, and itostrx.
 */
public class HW2Bases
{
	/**
	 * strdtoi - Decimal String to int
	 *
	 * Convert a string containing ASCII characters (in decimal) to an int.
	 * You do not need to handle negative numbers. The Strings we will pass in will be
	 * valid decimal numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strdtoi("123"); // => 123
	 */
	public static int strdtoi(String decimal)
	{
		int number = 0;
		int digit = 1;
		for (int i = decimal.length() - 1; i >= 0; i--) {
			number += digit * (decimal.charAt(i) - 48);
			digit *= 10;
		}
		return number;
	}

	/**
	 * strbtoi - Binary String to int
	 *
	 * Convert a string containing ASCII characters (in binary) to an int.
	 * You do not need to handle negative numbers. The Strings we will pass in will be
	 * valid binary numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strbtoi("111"); // => 7
	 */
	public static int strbtoi(String binary)
	{
		int number = 0;
		int digit = 0x0;
		for (int i = binary.length() - 1; i >= 0; i--) {
			number += (binary.charAt(i) - 48) << digit++;
		}
		return number;
	}

	/**
	 * strxtoi - Hexadecimal String to int
	 *
	 * Convert a string containing ASCII characters (in hex) to an int.
	 * The input string will only contain numbers and uppercase letters A-F.
	 * You do not need to handle negative numbers. The Strings we will pass in will be
	 * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strxtoi("A6"); // => 166
	 */
	public static int strxtoi(String hex)
	{
		int number = 0;
		int digit = 0x0;
		for (int i = hex.length() - 1; i >= 0; i--) {
			if (hex.charAt(i) <= 57) {
				number += (hex.charAt(i) - 48) << digit;
			} else {
				number += (hex.charAt(i) - 55) << digit;
			}
			digit += 0x4;
		}
		return number;
	}

	/**
	 * itostrb - int to Binary String
	 *
	 * Convert a int into a String containing ASCII characters (in binary).
	 * You do not need to handle negative numbers.
	 * The String returned should contain the minimum number of characters necessary to
	 * represent the number that was passed in.
	 * 
	 * Example: itostrb(7); // => "111"
	 */
	public static String itostrb(int binary)
	{
		String s = "";
		if (binary == 0) {
			return "0";
		}
		while (binary > 0) {
			int result = binary & 0x1;
			s = result + s;
			binary = binary >> 0x1;
		}
		return s;
	}

	/**
	 * itostrx - int to Hexadecimal String
	 *
	 * Convert a int into a String containing ASCII characters (in hexadecimal).
	 * The output string should only contain numbers and uppercase letters A-F.
	 * You do not need to handle negative numbers.
	 * The String returned should contain the minimum number of characters necessary to
	 * represent the number that was passed in.
	 * 
	 * Example: itostrx(166); // => "A6"
	 */
	public static String itostrx(int hex)
	{
		String s = "";
		int remainder = hex;
		if (hex == 0) {
			return "0";
		}
		while (hex > 0) {
			remainder = hex & 0xF;
			if (remainder >= 10) {
				s = (char) (remainder + 55) + s;
			} else {
				s = (char) (remainder + 48) + s;
			}
			hex = hex >> 0x4;
		}
		return s;
	}
}
