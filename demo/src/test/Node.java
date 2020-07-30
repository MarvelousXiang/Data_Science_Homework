package test;

import java.util.ArrayList;
import java.util.List;

public class Node
{
	private String name = "0"; // �����
	private Node parent; // �����
	private List<Node> children; // ���ӽ��
	private Integer fatherAttribution; // ���ڵ�����Ե�ֵ
	private Integer attribution;// ��ǰ��������
	private Boolean isLeaf = false;//�Ƿ�ΪҶ���

	public Integer getAttribution()
	{
		return attribution;
	}

	public void setAttribution(Integer attribution)
	{
		this.attribution = attribution;
	}

	public Boolean getIsLeaf()
	{
		return isLeaf;
	}

	public void setIsLeaf(Boolean isLeaf)
	{
		this.isLeaf = isLeaf;
	}

	private ArrayList<Integer> attributeSet;

	public String getName()
	{
		return name;
	}

	public void setName(String name)
	{
		this.name = name;
	}

	public Node getParent()
	{
		return parent;
	}

	public void setParent(Node parent)
	{
		this.parent = parent;
	}

	public List<Node> getChildren()
	{
		return children;
	}

	public void setChildren(List<Node> children)
	{
		this.children = children;
	}

	public Integer getFatherAttribution()
	{
		return fatherAttribution;
	}

	public void setFatherAttribution(Integer fatherAttribution)
	{
		this.fatherAttribution = fatherAttribution;
	}

	public ArrayList<Integer> getAttributeSet()
	{
		return attributeSet;
	}

	public void setAttributeSet(ArrayList<Integer> attributeSet)
	{
		this.attributeSet = attributeSet;
	}

	/**
	 * ���ӽ��
	 * 
	 * @param child
	 */
	public void addChildren(Node child)
	{
		if (this.getChildren() == null)
		{
			List<Node> list = new ArrayList<Node>();
			list.add(child);
			this.setChildren(list);
		} else
		{
			this.getChildren().add(child);
		}
	}

	/**
	 * ���ڷ��ؽ�㣬�����ڷ��ؿ�
	 * 
	 * @param name
	 * @return
	 */
	public Node findChild(String name)
	{
		List<Node> list = this.getChildren();
		if (list != null)
		{
			for (Node child : list)
			{
				if (child.getName().equals(name))
				{
					return child;
				}
			}
		}
		return null;
	}

}
