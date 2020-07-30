package test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Vector;

import javax.management.modelmbean.InvalidTargetObjectTypeException;

/**
 * ѵ����D������A 
 * ����TreeGenerate(D,A) 
 * { 
 *    ���ɽ��node;
 *    if D ������ȫ����ͬһ���C 
 *    then
 *       ��node���ΪC��������
 *       return; 
 *    end if 
 *    
 *    if AΪ��OR D��������A��ȡֵ��ͬ
 *    then
 *       ��node�����ΪҶ��㣬�������ΪD������������;
 *       return 
 *    end if
 * 
 *    ��A��ѡ�����Ż�������a 
 *    for a ��ÿһ��ȡֵai 
 *    {
 *       Ϊnode����һ����֧;
 *       �� Di ��ʾD����a��ȡֵΪai�������Ӽ�;
 *       if DiΪ��
 *       then 
 *          ����֧�ڵ���ΪҶ��㣬�������ΪD������������;
 *          return //ע��Di�ĸ��׽��ΪD 
 *       else
 *          ��TreeGenrate(Di,A\{a})Ϊ��֧���
 *       end if 
 *     } 
 * }
 * 
 * @author kepcum
 *
 */
public class Decision
{

	public static Vector<Integer> v_cold = new Vector<Integer>();
	public static Vector<Integer> v_middle = new Vector<Integer>();
	public static Vector<Integer> v_hot = new Vector<Integer>();
    
	public static int cout_leaf = 0;
	public static int count_node = 0;
	public static int k_l = Preprocessing.k_l;
	public static int train_l = Preprocessing.train_l;
	public static int total_l = Preprocessing.total_l;
	public static Node root = new Node();
	public static LinkedList<Integer[]> originData = new LinkedList<Integer[]>();
	public static LinkedList<Integer[]> testData = new LinkedList<Integer[]>();
	public static ArrayList<Integer> originAttri = new ArrayList<Integer>();// 33��������0-32��������ʾ
	//

	// ����1��2��3��������վ����ʵ����
	public static String realRating(int x)
	{
		if (x == 1)
			return "cold";
		if (x == 2)
			return "middle";
		return "hot";
	}

	/**
	 * ��ʼ��originAttri
	 */
	public static void initAttri()
	{
		for (int i = 0; i < k_l; i++)
		{
			originAttri.add(new Integer(i));
		}
	}

	/**
	 * ��ʼ��originData
	 */
	public static void initData()
	{
		for (int i = 0; i < total_l; i++)
		{
			Integer[] x = new Integer[k_l + 1];
			for (int j = 0; j < k_l + 1; j++)
			{
				x[j] = Preprocessing.train_arr[i][j];
			}
			if (i < train_l)
			{
				originData.add(x);
			} else
			{
				testData.add(x);
			}

		}
	}

	// ����������Ϣ���棬����ȡ����
	public static int maxGain(LinkedList<Integer[]> data, ArrayList<Integer> attri)
	{
		// ֻ��Ҫ����ai=1,ai=0ʱ��(D1/D)*(Ent(D1)) + (D0/D)*(Ent(D0))
		int minIndex = -1;
		double minEnt = 10000;
		int count = -1;
		for (Integer index : attri)
		{
			count++;
			double nowEnt = 0.0;
			index = (int) index;
			int[] dv = new int[2];
			Arrays.fill(dv, 0);
			int[][] couCla = new int[2][4];// ��couCla[0][3]�������ڸ�������ֵΪ0�����Ϊ3����������
			for (int i = 0; i < 2; i++)
			{
				Arrays.fill(couCla[i], 0);
			}

			for (int val = 0; val < 2; val++)
			{
				for (Integer[] subdata : data)
				{
					if (subdata[index].equals(new Integer(val)))
					{
						dv[val]++;
						couCla[val][subdata[k_l]]++;
					}
				}
			}

			double[][] entK = new double[2][4];
			for (int val = 0; val < 2; val++)
			{
				for (int i = 1; i < 4; i++)
				{
					if (couCla[val][i] == 0)
					{
						entK[val][i] = 0;
						continue;
					}
					double p = couCla[val][i] * 1.0 / (couCla[val][1] + couCla[val][2] + couCla[val][3]);// ÿ�������ռ�ı���
					entK[val][i] = -(p * (Math.log(p) / Math.log(2.0)));
				}
				nowEnt = nowEnt + 1.0 * dv[val] / data.size() * (entK[val][1] + entK[val][2] + entK[val][3]);//
			}
			if (count == 0 || nowEnt < minEnt)
			{
				minEnt = nowEnt;
				minIndex = index;
			}
		}
		return minIndex;

	}

	// �������������ࣨ1��2��3��
	public static int maxCountCla(LinkedList<Integer[]> data)
	{
		int[] cou_cla = new int[4];
		Arrays.fill(cou_cla, 0);
		for (Integer[] subdata : data)
		{
			cou_cla[subdata[k_l]]++;
		}
		int max = Math.max(cou_cla[1], Math.max(cou_cla[2], cou_cla[3]));
		for (int i = 1; i < 4; i++)
		{
			if (max == cou_cla[i])
				return cou_cla[i];
		}
		return cou_cla[3];
	}

	/**
	 * ������ĳЩ�����ϵ�ֵ�Ƿ���ͬ
	 */
	public static Boolean isLike(LinkedList<Integer[]> data, ArrayList<Integer> attri)
	{
		if (data == null || data.size() <= 1)
		{
			return true;
		}

		for (Integer index : attri)
		{
			int count = -1;
			Integer attVal = null;
			for (Integer[] subdata : data)
			{
				count++;
				if (count == 0)
				{
					attVal = subdata[index];
					continue;
				}
				if (!attVal.equals(subdata[index]))
				{
					return false;
				}
			}
		}
		return true;
	}

	/**
	 * ���ɾ�����
	 * 
	 * @param data
	 * @param attri
	 */
	public static void generateTree(LinkedList<Integer[]> data, ArrayList<Integer> attri, Node parent, Integer faAttri)
	{
		Node subnode = new Node();
		count_node++;
		subnode.setFatherAttribution(faAttri);
		subnode.setIsLeaf(false);
		subnode.setParent(parent);// ���õ�ǰ���ĸ����
		parent.addChildren(subnode);// ���õ�ǰ���Ϊ�����ĺ��ӽ��
		if (true)
		{
			int count = -1;
			Integer cla = 0;
			boolean flag = true;
			for (Integer[] subdata : data)
			{
				++count;
				if (count == 0)
				{
					cla = subdata[k_l];
				} else
				{
					if (!subdata[k_l].equals(cla))
					{
						flag = false;
						break;
					}
				}
			}
			if (flag)
			{
				subnode.setIsLeaf(true);
				++cout_leaf;
				subnode.setName(String.valueOf(cla));
				return;
			}
		}

		// attriΪ�գ���������������attri��ȡֵ��ͬ,��subnode���ΪҶ��㣬�������ΪD��������������
		if (attri == null || attri.size() == 0 || isLike(data, attri))
		{
			subnode.setIsLeaf(true);
			int cla = maxCountCla(data);
			subnode.setName(String.valueOf(cla));
			++cout_leaf;
			return;
		}
		// ��A��ѡ�����Ż�������a
		int attriIndex = maxGain(data, attri);
		subnode.setAttribution(new Integer(attriIndex));
		for (int val = 0; val < 2; val++)
		{
			LinkedList<Integer[]> newData = new LinkedList<Integer[]>();
			ArrayList<Integer> newAttri = new ArrayList<Integer>();
			for (Integer inte : attri)
			{
				if (inte.equals(new Integer(attriIndex)))
				{
					continue;
				}
				newAttri.add(inte);
			}
			for (Integer[] ddata : data)
			{
				if (ddata[attriIndex].equals(new Integer(val)))
				{
					newData.add(ddata);
				}
			}
			if (newData == null || newData.size() == 0)
			{
				Node nnode = new Node();
				nnode.setFatherAttribution(new Integer(val));
				nnode.setParent(subnode);
				subnode.addChildren(nnode);
				int claa = maxCountCla(newData);
				nnode.setIsLeaf(true);
				++cout_leaf;
				nnode.setName(String.valueOf(claa));
				++count_node;
				return;
			} else
			{
				generateTree(newData, newAttri, subnode, new Integer(val));
			}
		}
	}

	// ���������
	public static void printTree(Node root)
	{
		Vector<Node> vec = new Vector<Node>();
		int cou = 0;
		vec.add(root);
		int level = 0;
		while (!vec.isEmpty())
		{
			level++;
			int size = vec.size();
			// System.out.println("");
			// System.out.println("��"+level+"�㹲��"+size+"����㣬 ������£�");
			for (int i = 0; i < size; i++)
			{
				++cou;
				Node node = vec.get(0);
				vec.remove(0);
				if (node.getChildren() != null)
				{
					List<Node> list = node.getChildren();
					for (Node e : list)
					{
						vec.add(e);
					}
				}

			}
		}
	}

	// ���Ծ�����
	public static void testDecision()
	{
		int i = train_l - 1;
		int num_correct = 0;
		for (Integer[] data : testData)
		{
			++i;
			Node now_node = root;
			while (!now_node.getIsLeaf())
			{
				List<Node> list = now_node.getChildren();
				if (list.size() == 1)
				{
					now_node = list.get(0);
					continue;
				}
				for (Node e : list)
				{
					if (e.getFatherAttribution().equals(data[(int) now_node.getAttribution()]))
					{
						now_node = e;
						break;
					}
				}
			}
			String cla = now_node.getName();
			String rea_rating = realRating((int) (cla.charAt(0) - '0'));
			System.out.println("ʹ�þ�����Ԥ��URL= " + Preprocessing.set_tra_url[i] + "����վ�û�����Ϊ" + rea_rating);

			System.out.print("��վ����ʵ��Ϊ" + realRating(data[k_l]));
			if (rea_rating.equals(realRating(data[k_l])))
			{
				++num_correct;
				System.out.println("-------Ԥ����ȷ");
			} else
				System.out.println("-------Ԥ�����");
			System.out.println("*************************");
			System.out.println("");
		}
		// ͳ�ƾ������ķ���Ч��
		System.out.println("ѵ����������" + train_l + "  ѵ����������Ϊcold������" + v_cold.size() + "  ѵ����������Ϊmiddle������"
				+ v_middle.size() + "  ѵ����������Ϊhot������" + v_hot.size());
		System.out.println("���Լ�������" + (total_l - train_l) + "  Ԥ����ȷ��������" + num_correct + "  Ԥ��׼ȷ�ʣ�"
				+ (1.0 * num_correct / (total_l - train_l) * 100) + "%");
	}

	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		Preprocessing pre = new Preprocessing();
		pre.init();
		initAttri();
		initData();
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
		long startTime=System.currentTimeMillis();   //��ȡ��ʼʱ��
		generateTree(originData, originAttri, root, new Integer(-1));
		long endTime=System.currentTimeMillis(); //��ȡ������ģ�ͽ���ʱ��
		long startTime2=System.currentTimeMillis();   //��ȡ��ʼʱ��
		testDecision();//�Ѿ����ɵľ�����ģ�ͶԲ��Լ�Ԥ��
		long endTime2=System.currentTimeMillis(); //��ȡԤ�����ʱ��
		System.out.println("���ɾ�����ģ�͵�ʱ��Ϊ�� "+(endTime-startTime)+"ms");
		System.out.println("�������н������Ϊ"+count_node+"    Ҷ�ӽ��ĸ���Ϊ��" + cout_leaf);
		System.out.println("ʹ�þ�����ģ�ͶԲ��Լ�Ԥ���ʱ��Ϊ�� "+(endTime2-startTime2)+"ms");
		System.out.println("���̽���");
	}

}
