public class TestLinkedList<T> extends MySingleLinkedList<T> {

	public static void main(String[] args) {
		MySingleLinkedList<String>list = new MySingleLinkedList<>();
		list.addFirst("Sunday");
		list.add(1,"Monday");
		list.add(2,"Friday");
		list.add(0, "Thursday");
		list.remove("Friday");
		list.add(2, "Tuesday");
		list.add(4, "Wednesday");
		System.out.println(list.indexOf("Sunday"));
		
		for(int i=0;i<size;i++) {
			System.out.println(list.get(i));
		}
	}
}
