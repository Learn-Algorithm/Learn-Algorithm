package com.excelee.Algorithm;

import java.util.NoSuchElementException;


/***
 * 
 *这次作业基本是照着 caven 的抄了一遍
 *有一个问题是我创建后遍历出来的总是多一个0节点
 *删除删不掉
 */
public class OneAlgorithm {
	
	
	
	static BiObject bioRoot = new BiObject();
	
	//创建树
	public static void create(int[] numbers){
		for(int i=0;i<numbers.length;i++){
			insert(numbers[i]);
		}
	}
	//插入值
	public static void insert(int num){
		if(num<bioRoot.getData()){
			add(num,bioRoot,bioRoot.getLeftChild(),0);
		}else{
			add(num,bioRoot,bioRoot.getRightChild(),1);
		}
	}
	/***
	 * 
	 * @param num 插入的值
	 * @param bio 父节点
	 * @param bioChild 子节点
	 * @param lor 左右节点标记
	 */
	public static void add(int num,BiObject bio,BiObject bioChild,int lor){
		if(bioChild==null){
			bioChild = new BiObject();
			bioChild.setData(num);
			System.out.print(num+"--");
			if(0==lor){
				bio.setLeftChild(bioChild);
			}else{
				bio.setRightChild(bioChild);
			}
		}else{
			if(num<bioChild.getData()){
				add(num,bioChild,bioChild.getLeftChild(),0);
			}else if(num>bioChild.getData()){
				add(num,bioChild,bioChild.getRightChild(),1);
			}
		}
	}
	
	/***
	 * 查找值
	 * @param tree
	 * @param num
	 * @return
	 */
	public static BiObject search(BiObject tree,int num) {
		if(tree==null){
			throw new NoSuchElementException("值不存在");
		}
		if(num<tree.getData()){
			return search(tree.getLeftChild(), num);
		}else if(num>tree.getData()){
			return search(tree.getRightChild(), num);
		}else{
			return tree;
		}
		
	}
	/***
	 * 遍历
	 * @param tree
	 */
	public static void traversalTree(BiObject tree){
		if(tree == null){
			return;
		}
		traversalTree(tree.getLeftChild());
		System.out.print(tree.getData()+"--");
		traversalTree(tree.getRightChild());
	}
	
	/***
	 * 删除
	 * @param num
	 */
	public static void deleteAll(int num){
		delete(num, bioRoot);
	}
	public static void delete(int num,BiObject bio){
		if(bio!=null){
			if(num<bio.getData()){
				delete(num, bio.getLeftChild());
			}else if(num>bio.getData()){
				delete(num, bio.getRightChild());
			}else{
				System.out.println("bio : = null --"+bio.getData());
				bio = null;
			}
		}
	}
	public static void main(String[] args) {
		int nums[] = {5, 9, 2, 1, 4, 7, 6, 8};
		create(nums);
		System.out.println("\n第1次遍历  :");
		traversalTree(bioRoot);
		insert(3);
		System.out.println("\n第2次遍历 （增加3） :");
		traversalTree(bioRoot);
		System.out.println("\n第3次遍历  :");
		traversalTree(search(bioRoot,2));
		System.out.println("\n第4次遍历  :");
		deleteAll(1);
		traversalTree(bioRoot);
	}
}
/**节点对象 **/
class BiObject{
	
	private int data;
	private BiObject leftChild;
	private BiObject rightChild;
	public int getData() {
		return data;
	}
	public void setData(int data) {
		this.data = data;
	}
	public BiObject getLeftChild() {
		return leftChild;
	}
	public void setLeftChild(BiObject leftChild) {
		this.leftChild = leftChild;
	}
	public BiObject getRightChild() {
		return rightChild;
	}
	public void setRightChild(BiObject rightChild) {
		this.rightChild = rightChild;
	}
	
	
}

