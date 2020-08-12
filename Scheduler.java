package Scheduler;

import java.util.Arrays;
import java.util.Scanner;

public class Scheduler {
	
	private int capacity = 10;
	// 배열의 각 칸은 Event 타입. 여기서 다형성이 적용된다.(서브클래스가 부모클래스꺼 사용 가능)
	// 세 종류의 타입이 있다고 해서 각각 다른 배열을 만들필요 없고, 묶어서 할 수 있다(자바의 심장!!)(C와 다른점..)
	public Event []events = new Event[capacity];
	public int n=0;
	private Scanner kb;
	
	public void processCommand() {
		kb = new Scanner(System.in);
		while(true) {
			System.out.print("$ ");
			String command = kb.next();
			if(command.equals("addevent")) {
				String type = kb.next();
				if(type.equalsIgnoreCase("oneday"))
					handleAddOneDayEvent();
				else if (type.equalsIgnoreCase("duration"))
					handleAddDurationEvent();
				else if(type.equalsIgnoreCase("deadline"))
					handleAddDeadlineEvent();			
				
			}else if(command.equals("list")) {
				handleList();
				
			}else if(command.equals("show")) {
				handleShow();
				
			}else if(command.equals("sort")) {
				Arrays.sort(events,0,n);  // 좀 더 generic 한.
			}else if(command.equals("exit")) {
				break;		
			}
		}
		
	}
	private void handleShow() {
		String dateString = kb.next();
		MyDate theDate = parseDateString(dateString);
		for(int i=0;i<n;i++) {
			// test if events[i] is relevant to the date, then print it;
			if((events[i]).isRelevant(theDate))
				System.out.println(events[i].toString());
		}
		
	}
	private void handleList() {
		for(int i=0;i<n;i++) {
			System.out.println("  "+events[i].toString());
		}
		
	}
	private void handleAddDeadlineEvent() {
		System.out.print("  deadline: ");
		String dateString = kb.next();
		System.out.print("  title: ");
		String title = kb.next();
		
		MyDate date = parseDateString(dateString);
		DeadlinedEvent ev = new DeadlinedEvent(title,date);
		addEvent(ev);
		
	}
	private void handleAddDurationEvent() {
		System.out.print("  begin: ");
		String beginString = kb.next();
		System.out.print("  end: ");
		String endString = kb.next();
		System.out.print("  title: ");
		String title = kb.next();
		
		MyDate begin = parseDateString(beginString);
		MyDate end = parseDateString(endString);
		
		DurationEvent ev = new DurationEvent(title,begin,end);
		addEvent(ev);
		
	}
	private void handleAddOneDayEvent() {
		System.out.print("	when: ");
		String dateString = kb.next();
		
		System.out.print("	title: ");
		String title = kb.next();
		
		MyDate date = parseDateString(dateString);
		OneDayEvent ev = new OneDayEvent(title, date);
		System.out.println(ev.toString());
		
		addEvent(ev);
		
	}
	private void addEvent(Event ev) {
		if(n>=capacity)
			reallocate(); // 자바에서 제공해주는 메서드 중 하나!
		events[n++] = ev; // 여기서 다형성 적용!! OneDayEvent 타입의 객체를 Event타입의 배열에 저장함!		
	}
	private void reallocate() {
		Event []tmp = new Event[capacity * 2];
		for(int i=0;i<n;i++)
			tmp[i] = events[i];
		events = tmp;
		capacity *= 2;
	}
	private MyDate parseDateString(String dateString) {
		String []tokens = dateString.split("/");
		int year = Integer.parseInt(tokens [0]);
		int month = Integer.parseInt(tokens[1]);
		int day = Integer.parseInt(tokens[2]);
		
		MyDate d = new MyDate(year,month,day);
		return d;
	}
	public static void main(String[] args) {
		Scheduler app = new Scheduler();
		app.processCommand();
		
	}

}
