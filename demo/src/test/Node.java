package test;

import java.util.ArrayList;
import java.util.List;

public class Node
{
	private String name = "0"; // 结点名
	private Node parent; // 父结点
	private List<Node> children; // 孩子结点
	private Integer fatherAttribution; // 父节点的属性的值
	private Integer attribution;// 当前结点的属性
	private Boolean isLeaf = false;//是否为叶结点

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
	 * 增加结点
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
	 * 存在返回结点，不存在返回空
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
