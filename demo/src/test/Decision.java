package test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Vector;

import javax.management.modelmbean.InvalidTargetObjectTypeException;

/**
 * 训练集D，属性A 
 * 函数TreeGenerate(D,A) 
 * { 
 *    生成结点node;
 *    if D 中样本全属于同一类别C 
 *    then
 *       将node标记为C类样本；
 *       return; 
 *    end if 
 *    
 *    if A为空OR D中样本在A上取值相同
 *    then
 *       将node结点标记为叶结点，其类别标记为D中样本最多的类;
 *       return 
 *    end if
 * 
 *    从A中选出最优划分属性a 
 *    for a 的每一个取值ai 
 *    {
 *       为node生成一个分支;
 *       令 Di 表示D中在a上取值为ai的样本子集;
 *       if Di为空
 *       then 
 *          将分支节点标记为叶结点，其类别标记为D中样本最多的类;
 *          return //注意Di的父亲结点为D 
 *       else
 *          以TreeGenrate(Di,A\{a})为分支结点
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
	public static ArrayList<Integer> originAttri = new ArrayList<Integer>();// 33个属性用0-32的整数表示
	//

	// 输入1，2，3，返回网站的真实评级
	public static String realRating(int x)
	{
		if (x == 1)
			return "cold";
		if (x == 2)
			return "middle";
		return "hot";
	}

	/**
	 * 初始化originAttri
	 */
	public static void initAttri()
	{
		for (int i = 0; i < k_l; i++)
		{
			originAttri.add(new Integer(i));
		}
	}

	/**
	 * 初始化originData
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

	// 计算最大的信息增益，并获取属性
	public static int maxGain(LinkedList<Integer[]> data, ArrayList<Integer> attri)
	{
		// 只需要计算ai=1,ai=0时，(D1/D)*(Ent(D1)) + (D0/D)*(Ent(D0))
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
			int[][] couCla = new int[2][4];// 如couCla[0][3]，代表在该属性上值为0，类别为3的样本总数
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
					double p = couCla[val][i] * 1.0 / (couCla[val][1] + couCla[val][2] + couCla[val][3]);// 每个类别所占的比例
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

	// 返回样本最多的类（1，2，3）
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
	 * 样本在某些属性上的值是否相同
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
	 * 生成决策树
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
		subnode.setParent(parent);// 设置当前结点的父结点
		parent.addChildren(subnode);// 设置当前结点为父结点的孩子结点
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

		// attri为空，或者所有数据在attri上取值相同,将subnode标记为叶结点，其类别标记为D中样本数最多的类
		if (attri == null || attri.size() == 0 || isLike(data, attri))
		{
			subnode.setIsLeaf(true);
			int cla = maxCountCla(data);
			subnode.setName(String.valueOf(cla));
			++cout_leaf;
			return;
		}
		// 从A中选择最优化分属性a
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

	// 输出决策树
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
			// System.out.println("第"+level+"层共有"+size+"个结点， 结点如下：");
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

	// 测试决策树
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
			System.out.println("使用决策树预测URL= " + Preprocessing.set_tra_url[i] + "的网站用户评级为" + rea_rating);

			System.out.print("网站的真实评为" + realRating(data[k_l]));
			if (rea_rating.equals(realRating(data[k_l])))
			{
				++num_correct;
				System.out.println("-------预测正确");
			} else
				System.out.println("-------预测错误");
			System.out.println("*************************");
			System.out.println("");
		}
		// 统计决策树的分类效果
		System.out.println("训练集数量：" + train_l + "  训练集中评级为cold数量：" + v_cold.size() + "  训练集中评级为middle数量："
				+ v_middle.size() + "  训练集中评级为hot数量：" + v_hot.size());
		System.out.println("测试集数量：" + (total_l - train_l) + "  预测正确的数量：" + num_correct + "  预测准确率："
				+ (1.0 * num_correct / (total_l - train_l) * 100) + "%");
	}

	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		Preprocessing pre = new Preprocessing();
		pre.init();
		initAttri();
		initData();
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
		long startTime=System.currentTimeMillis();   //获取开始时间
		generateTree(originData, originAttri, root, new Integer(-1));
		long endTime=System.currentTimeMillis(); //获取决策树模型结束时间
		long startTime2=System.currentTimeMillis();   //获取开始时间
		testDecision();//已经生成的决策树模型对测试集预测
		long endTime2=System.currentTimeMillis(); //获取预测结束时间
		System.out.println("生成决策树模型的时间为： "+(endTime-startTime)+"ms");
		System.out.println("决策树中结点总数为"+count_node+"    叶子结点的个数为：" + cout_leaf);
		System.out.println("使用决策树模型对测试集预测的时间为： "+(endTime2-startTime2)+"ms");
		System.out.println("进程结束");
	}

}
