package test;

import java.util.Vector;

public class NaiveBayesClassifier
{
	/**
	 * ����k����� ,���Ƿֱ���1��2��3����ʾ�������cold,middle,hot�� m��ѵ������m = train_l = 51 n������������n =
	 * k_l = 33 p(yj|x)=( p(xi|yj) * p(yi)) / (p(x))
	 * ���������yj����ĸ�ϵ�p(x)����ͬ�����Կ��Բ����㡣�����p(yj|x) = ��
	 * ����yi���ĸ���/train_l��II(����yj�����iλ��Ϊxi����������/����yi���������ĸ���)
	 */
	//����Ϊint�������Ӧ��String��
	public static String toStringCla(int x)
	{
		if(x==1)
			return "cold";
		else if(x==2)
			return "middle";
		else
			return "hot";
	}
	public static void byes()// ��Ҷ˹������
	{
		long startTime=System.currentTimeMillis();   //��ȡ��ʼʱ��
		int k_l = Preprocessing.k_l;
		int train_l = Preprocessing.train_l;
		int total_l = Preprocessing.total_l;
		double accuracy = 0;
		int num_correct = 0;
		Vector<Integer> v_cold = new Vector<Integer>();
		Vector<Integer> v_middle = new Vector<Integer>();
		Vector<Integer> v_hot = new Vector<Integer>();
		// ͳ�Ƹ��������������
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
		// ͳ�Ƹ��������ѵ������������
		int[][][] num = new int[3][k_l][2];// ��num[1][1][1]�洢���ڵ�2�����ĵ�2������ֵΪ1��ѵ�������ĸ���
		for (int i = 0; i < train_l; i++)
		{
			int cla = Preprocessing.train_arr[i][k_l] - 1;// �������
			for (int j = 0; j < k_l; j++)
			{
				int character = Preprocessing.train_arr[i][j];// ����ֵ��ȡֵ0����1
				num[cla][j][character]++;
			}
		}
		//
		for (int i = train_l; i < total_l; i++)
		{
			double p_cold = 1.0 * v_cold.size() / train_l;
			double p_middle = 1.0 * v_middle.size() / train_l;
			double p_hot = 1.0 * v_hot.size() / train_l;

			int cla = Preprocessing.train_arr[i][k_l];// ��ʵ����
			String real_rating = null;
			if (cla == 1)
				real_rating = "cold";
			else if (cla == 2)
				real_rating = "middle";
			else
				real_rating = "hot";

			for (int j = 0; j < k_l; j++)// ����ÿ�ַ���ֱ��Ӧ�ĸ���
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
			System.out.println("ʹ�ñ�Ҷ˹������Ԥ��URL= " + Preprocessing.set_tra_url[i] + " ����վ�û�����Ϊ��"+stringCla);
			System.out.print("��վ����ʵ����Ϊ��" + real_rating);
			if(real_rating.equals(stringCla))
			{
				num_correct++;
				System.out.println("-------Ԥ����ȷ");
			}
			else
				System.out.println("-------Ԥ�����");
			System.out.println("*************************");
			System.out.println();

		}
		// ͳ�Ʊ�Ҷ˹�������ķ���Ч��
		System.out.println("ѵ����������" + train_l + "  ѵ����������Ϊcold������" + v_cold.size() + "  ѵ����������Ϊmiddle������"
				+ v_middle.size() + "  ѵ����������Ϊhot������" + v_hot.size());
		System.out.println("���Լ�������" + (total_l - train_l) + "  Ԥ����ȷ��������" + num_correct + "  Ԥ��׼ȷ�ʣ�"
				+ (1.0 * num_correct / (total_l - train_l) * 100) + "%");
		
		long endTime=System.currentTimeMillis(); //��ȡ����ʱ��
		System.out.println("ʹ�ñ�Ҷ˹����������ģ�ͼ�Ԥ�����ݵ���ʱ��Ϊ�� "+(endTime-startTime)+"ms");
	}

	public static void main(String[] args)
	{

		// TODO Auto-generated method stub

		Preprocessing pre = new Preprocessing();
		pre.init();
		// ʹ�ñ�Ҷ˹������
		byes();

	}

}
