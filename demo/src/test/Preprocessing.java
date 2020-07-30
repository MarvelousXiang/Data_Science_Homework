package test;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/**
 * 
 * 预处理类
 *
 */

public class Preprocessing
{

	public static String[] keywords = null;
	public static int k_l = 33;
	public static int train_l = 287;
	public static int total_l = 327;
	public static int[][] train_arr = new int[total_l + 10][k_l + 10];
	public static String[] set_tra_url = new String[total_l + 10];

	public Preprocessing()
	{

	}

	public void init()
	{
		long startTime=System.currentTimeMillis();   //获取开始时间
		// 读取关键字，并存入数组中
		try
		{
			File file = new File("src/test/load_key");
			BufferedReader br = new BufferedReader(new FileReader(file));
			String str = null;
			while ((str = br.readLine()) != null)
			{
				str = str.trim();
				keywords = str.split(",");
			}
			br.close();
		} catch (Exception e)
		{
			e.printStackTrace();
		}
		k_l = keywords.length;// 注意length后面没有()

		// System.out.println(k_l);
		// 对网页的源码做此法分析器，并放入set集合中
		// String[] set_tra_url= new String[total_l+10];
		int m = 0;
		try
		{
			File file = new File("src/test/url");
			BufferedReader br = new BufferedReader(new FileReader(file));
			String str = null;
			while ((str = br.readLine()) != null)
			{
				str = str.trim();
				set_tra_url[m++] = str;
			}
			br.close();
		} catch (Exception e)
		{
			e.printStackTrace();
		}

		m = 0;
		while (m < total_l)
		{
			read_file(set_tra_url[m], m++);
		}
		read_rating();
		long endTime=System.currentTimeMillis(); //获取结束时间
		System.out.println("数据预处理运行时间为： "+(endTime-startTime)+"ms");
	}

	// 读取源代码并提取特征向量
	public void read_file(String url, int m)
	{
		// 对源代码次词法分析，并放入set_file_word集合
		Set<String> set_file_word = new HashSet<String>();
		try
		{
			File file = new File(url);
			BufferedReader br = new BufferedReader(new FileReader(file));
			String str = null;
			while ((str = br.readLine()) != null)
			{
				str.trim();
				str = str.toLowerCase();
				String f_word = "";
				for (int i = 0; i < str.length();)
				{
					if (Character.isLetter(str.charAt(i)))
					{
						f_word = "";
						for (; i < str.length();)
						{
							if (Character.isLetter(str.charAt(i)))
							{
								f_word = f_word + str.charAt(i);
								i++;
							} else
							{
								set_file_word.add(f_word);
								break;
							}
						}
					} else
					{
						i++;
					}
				}
			}
			br.close();
		} catch (Exception e)
		{
			e.printStackTrace();
		}
		for (int i = 0; i < k_l; i++)
		{
			if (set_file_word.contains(keywords[i]))
			{
				train_arr[m][i] = 1;
			} else
				train_arr[m][i] = 0;
		}
		/*
		 * System.out.println("************文件源地址为："+url); Iterator<String> it =
		 * set_file_word.iterator(); while (it.hasNext()) { String str = it.next();
		 * 
		 * System.out.println("   "+str); }
		 */
	}

	// 读取训练集的rating
	public void read_rating()
	{
		String[] str_rat = new String[total_l + 10];

		try
		{
			File file = new File("src/test/index");
			BufferedReader br = new BufferedReader(new FileReader(file));
			String str = null;
			int m = 0;
			while ((str = br.readLine()) != null)
			{
				str = str.trim();
				str_rat = str.split("\\|");
				if (str_rat[1].charAt(0) == 'c')
				{
					train_arr[m][k_l] = 1;
				} else if (str_rat[1].charAt(0) == 'm')
				{
					train_arr[m][k_l] = 2;
				} else
				{
					train_arr[m][k_l] = 3;
				}
				m++;
			}
			br.close();
		} catch (Exception e)
		{
			e.printStackTrace();
		}
	}

}
