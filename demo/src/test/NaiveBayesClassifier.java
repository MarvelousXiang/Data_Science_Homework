package test;

import java.util.Vector;

public class NaiveBayesClassifier
{
	/**
	 * 设有k个类别 ,我们分别用1，2，3来表示三个类别cold,middle,hot。 m个训练集，m = train_l = 51 n个特征向量，n =
	 * k_l = 33 p(yj|x)=( p(xi|yj) * p(yi)) / (p(x))
	 * 对于任意得yj，分母上得p(x)都相同，所以可以不计算。化简得p(yj|x) = （
	 * 属于yi类别的个数/train_l）II(属于yj类别中i位置为xi得样本个数/属于yi类别的样本的个数)
	 */
	//参数为int返回类对应的String类
	public static String toStringCla(int x)
	{
		if(x==1)
			return "cold";
		else if(x==2)
			return "middle";
		else
			return "hot";
	}
	public static void byes()// 贝叶斯分类器
	{
		long startTime=System.currentTimeMillis();   //获取开始时间
		int k_l = Preprocessing.k_l;
		int train_l = Preprocessing.train_l;
		int total_l = Preprocessing.total_l;
		double accuracy = 0;
		int num_correct = 0;
		Vector<Integer> v_cold = new Vector<Integer>();
		Vector<Integer> v_middle = new Vector<Integer>();
		Vector<Integer> v_hot = new Vector<Integer>();
		// 统计各类别样本的数量
		for (int i = 0; i < train_l; i++)
		{
			if (Preprocessing.train_arr[i][k_l] == 1)
			{
				v_cold.add(i);
			} else if (Preprocessing.train_arr[i][k_l] == 2)
			{
				v_middle.add(i);
			} else
			{
				v_hot.add(i);
			}
		}
		// 统计各中情况的训练样本的数量
		int[][][] num = new int[3][k_l][2];// 如num[1][1][1]存储属于第2个类别的第2个特征值为1的训练样本的个数
		for (int i = 0; i < train_l; i++)
		{
			int cla = Preprocessing.train_arr[i][k_l] - 1;// 所属类别
			for (int j = 0; j < k_l; j++)
			{
				int character = Preprocessing.train_arr[i][j];// 特征值的取值0或者1
				num[cla][j][character]++;
			}
		}
		//
		for (int i = train_l; i < total_l; i++)
		{
			double p_cold = 1.0 * v_cold.size() / train_l;
			double p_middle = 1.0 * v_middle.size() / train_l;
			double p_hot = 1.0 * v_hot.size() / train_l;

			int cla = Preprocessing.train_arr[i][k_l];// 真实分类
			String real_rating = null;
			if (cla == 1)
				real_rating = "cold";
			else if (cla == 2)
				real_rating = "middle";
			else
				real_rating = "hot";

			for (int j = 0; j < k_l; j++)// 计算每种分类分别对应的概率
			{
				int character = Preprocessing.train_arr[i][j];			
				p_cold = p_cold * 1.0 * num[0][j][character] / v_cold.size();
				p_middle = p_middle * 1.0 * num[1][j][character] / v_middle.size();
				p_hot = p_hot * 1.0 * num[2][j][character] / v_hot.size();
			}
			System.out.println(p_cold + "  " + p_middle + "  " + p_hot);
			double p = Math.max(Math.max(p_cold, p_middle), p_hot);
			//printAnswer
			String stringCla;
			if(p == p_cold)
				stringCla = toStringCla(1);
			else if(p == p_middle)
				stringCla = toStringCla(2);
			else
				stringCla = toStringCla(3);
			System.out.println("使用贝叶斯分类器预测URL= " + Preprocessing.set_tra_url[i] + " 的网站用户评级为："+stringCla);
			System.out.print("网站的真实评级为：" + real_rating);
			if(real_rating.equals(stringCla))
			{
				num_correct++;
				System.out.println("-------预测正确");
			}
			else
				System.out.println("-------预测错误");
			System.out.println("*************************");
			System.out.println();

		}
		// 统计贝叶斯分类器的分类效果
		System.out.println("训练集数量：" + train_l + "  训练集中评级为cold数量：" + v_cold.size() + "  训练集中评级为middle数量："
				+ v_middle.size() + "  训练集中评级为hot数量：" + v_hot.size());
		System.out.println("测试集数量：" + (total_l - train_l) + "  预测正确的数量：" + num_correct + "  预测准确率："
				+ (1.0 * num_correct / (total_l - train_l) * 100) + "%");
		
		long endTime=System.currentTimeMillis(); //获取结束时间
		System.out.println("使用贝叶斯分类器建立模型及预测数据的总时间为： "+(endTime-startTime)+"ms");
	}

	public static void main(String[] args)
	{

		// TODO Auto-generated method stub

		Preprocessing pre = new Preprocessing();
		pre.init();
		// 使用贝叶斯分类器
		byes();

	}

}
