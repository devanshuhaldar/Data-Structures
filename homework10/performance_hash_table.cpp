#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// defined in performance.cpp
void usage();

template <class T>
void hash_sort(unordered_map<T,int>& hash, ostream& ostr, int& output_count ){ //go through hash table find smallest value, then loop again find next smallest
  //Not Feasible
}

template <class T>
void hash_remove_duplicates(unordered_set<T>& hash, ostream& ostr, int& output_count){
  output_count = 0;
  for (typename unordered_set<T>::iterator itr = hash.begin(); itr!=hash.end(); itr++){
   // ostr<<*itr<<"\n";
    output_count++;
  }
}

template <class T>
void hash_mode(unordered_map<T,int>& hash, ostream& ostr, int& output_count){
  typename unordered_map<T,int>::iterator init = hash.begin();
  for (typename unordered_map<T,int>::iterator itr = hash.begin(); itr != hash.end(); itr++){
    if (init->second < itr->second){
      init = itr;
    }
  }
  ostr<<init->first<<"\n";
  output_count = 1;
}

void hash_closest_pair(unordered_map<int,int>& hash, ostream& ostr, int& output_count){
  //Not Feasible

}

template <class T>
void hash_first_sorted(unordered_map<T,int>& hash, ostream& ostr, int& output_count, int optional_arg){
  //not feasible
}

void hash_longest_substring(unordered_set<string>& hash, ostream& ostr, int& output_count){
  int best_size = 0;
  string best_str;
  for (unordered_set<string>::iterator i = hash.begin(); i != hash.end(); i++){
    for (unordered_set<string>::iterator j = i; j != hash.end(); j++){ // same explanation as vector cpp
      string str = "";
      string str2 = "";
      string word1 = *i;
      string word2 = *j;
      if (word1 != word2){
        if (word1.size() >= word2.size()){
          for (int gen = 0 ; gen < word2.size(); gen++){
            str2 = "";
            for (int small = gen; small < word2.size(); small++){
              str2+=word2[small];
              str = "";
              for (int large = 0; large < word1.size(); large++){
                str+=word1[large];
                if (str2 == str){
                  if (str.size() > best_size){
                    best_str = str;
                    best_size = str.size();
                  }
                }
              }
            }
          }
        }else{//word2 greater
          for (int gen = 0 ; gen < word2.size(); gen++){
            str2 = "";
            for (int small = gen; small < word1.size(); small++){
              str2+=word1[small];
              str = "";
              for (int large = 0; large < word2.size(); large++){
                str+=word2[large];
                if (str2 == str){
                  if (str.size() > best_size){
                    best_str = str;
                    best_size = str.size();
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  ostr<<best_str<<std::endl;
}

void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your hash table like this:
  // std::unordered_set<std::string> ht;
  // OR 
  // std::unordered_map<std::string,int> ht;
   if (type == "string"){
    std::unordered_set<std::string> hash;
    unordered_map<string, int> ump;
    std::string s;
    input_count = 0;
    int sprev = 0;
    while (istr >> s) {
      if (operation == "remove_duplicates" || operation == "longest_substring"){
        hash.insert(s);
        if (sprev < hash.size()){
          if (operation == "remove_duplicates")
            ostr<<s<<std::endl;
          sprev++;
        }
      }
      ump[s] += 1;
      input_count++;
    }
    if (operation == "sort")                      {hash_sort(ump,ostr,output_count);}
    else if (operation == "remove_duplicates")  {hash_remove_duplicates(hash,ostr,output_count); } 
    else if (operation == "mode")              { hash_mode              (ump,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { hash_first_sorted      (ump,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { hash_longest_substring (hash,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  else {
    assert (type == "integer");
    // load the data into a hash of integers
    std::unordered_set<int> hash;
    unordered_map<int, int> ump;
    int v;
    input_count = 0;
    int sprev = 0;
    while (istr >> v) {
      if (operation == "remove_duplicates"){
        hash.insert(v);
        if (sprev < hash.size()){
          ostr<<v<<std::endl;
          sprev++;
        }
      }
      ump[v] += 1;
      input_count++;
    }
    if (operation == "sort")                    {hash_sort(ump,ostr,output_count);}
    else if (operation == "remove_duplicates")  {hash_remove_duplicates(hash,ostr,output_count); }
    else if (operation == "mode")              { hash_mode              (ump,ostr,output_count); }
    else if (operation == "closest_pair")      { hash_closest_pair      (ump,ostr,output_count); }
    else if (operation == "first_sorted")      { hash_first_sorted      (ump,ostr,output_count,optional_arg); }
    // "longest_suhashring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }


/*
  std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  exit(0);*/
}






//
//package hw8;
//
//// Lots of includes to do everything
//import java.awt.BasicStroke;
//import java.awt.Color;
//import java.awt.Graphics;
//import java.awt.Graphics2D;
//import java.awt.Image;
//import java.awt.image.BufferedImage;
//import java.io.File;
//import java.io.IOException;
//import java.util.ArrayList;
//import javax.imageio.ImageIO;
//import javax.swing.JPanel;
//import java.util.Map;
//import java.util.AbstractMap;
//import hw7.CampusModel;
////import javafx.util.Pair;
//
//
//// We didn't have to write ADT specifications and Rep invariants so there are none
//public class imagemaker extends JPanel{
//	private static final long serialVersionUID = -399264903588448546L;// I was getting a serial warning
//	private BufferedImage image; // Save the original image saved, modify the other one to avoid
//	private Image drawn_image;   // Having the image get distorted
//	final static int ORG_H = 2050; // I always cut the image so I need to div. by 2050, not 3400.
//	final static int ORG_W = 2175; // These are used for scaling
//	int width;
//	int height;
//	boolean lines; // Determines in PaintComponent Whether to draw lines/markers.
//	boolean marker;
//	ArrayList<Map.Entry<Double, Double>> points; // Points to draw lines
//	Map.Entry<Double, Double> start; // Start/End Points
//	Map.Entry<Double, Double> end;
//	/**
//	 * @param CampusModel object
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @modifies image, drawn_image, lines, marker, points 
//	 * @effects Reads in an image using a set fileline, also sets lines/marker to false and points,
//	 * star, and end to null
//	 */
//	// Constructor for my ImagePanel
//	public imagemaker(CampusModel CampusMap) {
//		try { // Try Catch in case reading in the image fails
//			image = ImageIO.read(new File("data/RPI_campus_map_2010_extra_nodes_edges.png"));
//			image = image.getSubimage(0, 0, 2175, 2050);
//			drawn_image = image; // Image is cropped and copied, variables initialized
//			lines = false;
//			marker = false;
//			points = null;
//			start = null;
//			end = null;
//		} 
//		catch (IOException ex) {ex.printStackTrace();}
//	}
//	/**
//	 * @param N/A
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @effects drawn_image is reset to a scaled and smoothed version of the original
//	 * @modifies drawn_image
//	 */
//	public void Initialize() // Resets the drawn_image back to the original one
//	{ // The most important bit is the smoothing so it is more legible
//		drawn_image = image.getScaledInstance(width, height, Image.SCALE_SMOOTH);
//	}
//	/**
//	 * @param Graphics g
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @effects changes width/height to the minimum of either of the window sizes, also paints image
//	 * @modifies width/height also the panel as it draws, follows paintComponent specs
//	 */
//	@Override // Main function for painting, its a callback
//	protected void paintComponent(Graphics g) {
//		super.paintComponent(g);
//        Graphics2D g2 = (Graphics2D) g;
//		width = Math.min(this.getWidth(), this.getHeight()); // Find the correct width/height
//		height = Math.min(this.getWidth(), this.getHeight());
//        g.drawImage(drawn_image, 0, 0, Math.min(width, height), 
//        		Math.min(width, height),this); // Draws the image as a square
//        g2.setStroke(new BasicStroke(5));      // Sets the stroke, line thickness
//        if(lines)
//        {
//        	g2.setColor(Color.BLUE); // I selected blue for the contrast it would provide
//        	for(int i = 1; i < points.size(); i++)
//        	{ // Draws the lines to make the path
//        		g.drawLine(points.get(i-1).getKey().intValue(), points.get(i-1).getValue().intValue(), 
//        				points.get(i).getKey().intValue(), points.get(i).getValue().intValue());
//        	}
//        	g2.setColor(Color.GREEN); // Green to indicate start
//        	g2.setColor(Color.RED);  // Red to indicate end
//        	lines = false; // The lines need to disappear next time a path is selected.
//        }
//        if(start != null) // If a start point has been added, draw it
//        {
//        	g2.setColor(Color.GREEN); // Green to indicate start, draws a hollow marker
//        	g2.drawOval(start.getKey().intValue()-5, 
//        			start.getValue().intValue()-5, 10, 10);
//        }
//        if(end != null) // If a end point has been added, draw it
//        {
//        	g2.setColor(Color.RED); // Green to indicate start
//        	g2.drawOval(end.getKey().intValue()-5, 
//        			end.getValue().intValue()-5, 10, 10);
//        }
//	}
//	/**
//	 * @param Map.Entry<Double, Double> start, the start point coordinates
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @effects sets marker to true and alters the start point by scaling it to the correct size
//	 * @modifies start and cirlce
//	 */
//	public void Set_Start(Map.Entry<Double, Double> start)
//	{ // Takes a point and sets it to the start, also rescales the points values to image size
//		marker = true;
//		Map.Entry<Double, Double> new_point = new AbstractMap.SimpleEntry<Double, Double>
//		(start.getKey()*((float)width/ORG_W),start.getValue()*((float)height/ORG_H));
//		this.start = new_point;
//	}
//	/**
//	 * @param Map.Entry<Double, Double> end, the end point coordinates
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @effects sets marker to true and alters the start point by scaling it to the correct size
//	 * @modifies end and cirlce
//	 */
//	public void Set_End(Map.Entry<Double, Double> end) {
//		marker = true;
//		Map.Entry<Double, Double> new_point = new AbstractMap.SimpleEntry<Double, Double>
//		(end.getKey()*((float)width/ORG_W),end.getValue()*((float)height/ORG_H));
//		this.end = new_point;
//	}
//	/**
//	 * @param ArrayList<Map.Entry<Double, Double>> points, the set of all points in order
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @effects sets marker to true and alters the start point by scaling it to the correct size
//	 * @modifies end and marker
//	 */
//	// Function used to tell the class it can draw these lines
//	public void Draw_lines(ArrayList<Map.Entry<Double, Double>> points)
//	{
//		this.points = points;
//		lines = true;
//    	Scale_to_Image(width, height, ORG_W, ORG_H);
//	}
//	/**
//	 * @param int width, height, original_w, and orginal_h, all variables used for scaling purposes
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @effects alters all the points by scaling them to the correct size and 
//	 * 			setting points = new_points
//	 * @modifies points
//	 */
//	// Scales the lines to current image size
//	private void Scale_to_Image(int width, int height, int original_w, int original_h)
//	{
//		ArrayList<Map.Entry<Double, Double>> new_points = new ArrayList<Map.Entry<Double, Double>>();
//		Map.Entry<Double, Double> new_point; // Makes new array of points
//		for(int i = 0; i < points.size(); i++) // proceeds to scale all old points and put them in new
//		{
//		new_point = new AbstractMap.SimpleEntry<Double, Double>(points.get(i).getKey()*((float)width/ORG_W),
//				points.get(i).getValue()*((float)height/ORG_H));
//		new_points.add(new_point);
//		}
//		points = new_points; // Sets the old points to the new points
//	}
//	/**
//	 * @param N/A
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @effects sets drawn_image back to image, sets lines to false, start to null, and end to null
//	 * @modifies lines, drawn_image, start, and end
//	 */
//	// Resets Image Panel back to original state except for smoothing
//	public void Reset()
//	{
//		drawn_image = image;
//		lines = false;
//		start = null;
//		end = null;
//	}
//	/**
//	 * @param N/A
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @effects sets start to null
//	 * @modifies start
//	 */
//	public void ResetStart() {
//		start = null;	// Resets the start point so it isn't drawn
//	}
//	/**
//	 * @param N/A
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @effects sets end to null
//	 * @modifies end
//	 */
//	public void ResetEnd() {
//		end = null;	// Resets the end point so it isn't drawn
//	}
//}

































//package hw8;
//
////Lots of includes to do everything
//import java.awt.*;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//import java.util.ArrayList;
//import javax.swing.JButton;
//import javax.swing.JComboBox;
//import javax.swing.JFrame;
//import javax.swing.JLabel;
//import javax.swing.JOptionPane;
//import javax.swing.JTextField;
//import javax.swing.SwingConstants;
//import hw7.CampusModel;
//import hw7.BuildingList;
//import javafx.util.Pair;
//import java.util.Map;
//import java.util.AbstractMap;
////import javafx.util.Pair;
//
//// No ADT Specifications as we were told, same with Represenation Invariant
//public class RPICampusPathsMain {
//	final static boolean shouldFill = true; // Some defined static variables
//	final static boolean shouldWeightX = true;
//	final static boolean RIGHT_TO_LEFT = false;
//	final static double D_Conv = 1474.30077497;
//	final static double T_Conv = 73.7150387485;
//	final static Map.Entry<Double, Double> Pizza_Loc = new AbstractMap.SimpleEntry<Double, Double>(892.0, 1605.0);
//
//	/**
//	 * @param Container pane (the pane I add to), CampusModel CampusMap (for path-finding),
//	 *		  and a JButton Reset so I can press a button from outside the method, described why later
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @modifies pane, Reset is added to pane 
//	 * @effects pane has components to it, a layout designated, orientation defined, components
//	 * 			added listed here:
//	 * 			Start, End, Starting, Ending, Help, Reset, Pizza, Text_Path, Draw_Iterative, Quit,
//	 * 			Calculate, i_panel
//	 */
//	// I do most of everything here except for a function or two, mostly because its just a lot of
//	// component adding and defining, which all has to be done in the pane since I am not using 
//	// multiple panels, just one. I also have a few nested calculations and a tiny bit of duplicate
//	// code because they were doing very different things using similar methods that couldn't be 
//	// extracted without changing the model. But thats a small portion and fairly neglible.
//	public static void addComponentsToPane(Container pane,  CampusModel CampusMap, JButton Reset) 
//	{
//		// Start off by making my i_panel variable which I will need often as it holds my image
//		imagemaker i_panel = new imagemaker(CampusMap);
//		// Some GridBag Layout constraints, orientations, etc
//		String[] choices = BuildingList.B_Command(CampusMap).split("\n");
//		if (RIGHT_TO_LEFT) {
//			pane.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
//		}
//		pane.setLayout(new GridBagLayout());
//		GridBagConstraints c = new GridBagConstraints();
//		if (shouldFill) {
//			c.fill = GridBagConstraints.HORIZONTAL;
//		}
//
////=====================================================================================================
//// Start Component, textfield for the start. Holds the text value, either building name or id, of
//// the starting location, only tricky thing is the image only updates when enter is pressed, but that
//// is stated in the help menu
//		JTextField Start = new JTextField(6);
//		Start.setText("Enter your Starting Location Here"); // initial state
//		if (shouldWeightX) {
//			c.weightx = 0.5;
//		}
//		c.fill = GridBagConstraints.HORIZONTAL; // Layout Constraints
//		c.gridx = 0;
//		c.gridy = 1;
//		pane.add(Start, c); // Component is added to the the pane
//		Start.addActionListener(new ActionListener()
//		{ // If enter is pressed, takes the text field and tries to add a start point to the map
//		  // if it is not a start point it opens up a JOptionPane and notifies the user that it is
//		  // an invalid point, so not a building name or ID. Special Case for Bella's Pizza, see
//		  // Pizza Component for more information
//			public void actionPerformed(ActionEvent e) {
//				String Start_ = strip(Start.getText()); // I have functionality to strip extra 
//				if(CampusMap.is_Building(Start_))       // whitespace, Only at the end of course
//				{	// when enter is pressed the start is set and circle at the location drawn
//					i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//				}
//				else // Otherwise, if it is invalid, it resets start if it did exist and notifies user
//				{
//					if(Start_.equals("Bella's Pizza"))
//					{
//						i_panel.ResetStart();
//						String text = "There is no better decision\nBut this is an Invalid Start "
//								+ "Location\nThis location is only for use with the Good Decision"
//								+ " Button";
//						JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//								JOptionPane.INFORMATION_MESSAGE);
//					}
//					else
//					{
//						i_panel.ResetStart();
//						String text = "Invalid Start Building\nPlease Enter a either a Building Name or "
//								+ "corresponding ID\n(Intersections are invalid input)";
//						JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//								JOptionPane.INFORMATION_MESSAGE);
//					}
//				}
//				i_panel.repaint();
//				i_panel.Initialize();
//			}
//		});
////=====================================================================================================
//// End Component, the same as start except for the Pizza Corner Case, everything else is the same
//// but for the End values.
//		JTextField End = new JTextField(6);
//		End.setText("Enter your Ending Destination Here");
//		c.fill = GridBagConstraints.HORIZONTAL;
//		c.weightx = 0.5;
//		c.gridx = 1;
//		c.gridy = 1;
//		pane.add(End, c);
//		End.addActionListener(new ActionListener()
//		{
//			public void actionPerformed(ActionEvent e) {
//				String End_ = strip(End.getText());
//				if(CampusMap.is_Building(End_))
//				{
//					i_panel.Set_End(CampusMap.get_Coord(CampusMap.get_ID(End_)));
//				}
//				else
//				{
//					i_panel.ResetEnd();
//					String text = "Invalid End Building\nPlease Enter a either a Building Name or "
//							+ "corresponding ID\n(Intersections are invalid input)";
//					JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//							JOptionPane.INFORMATION_MESSAGE);
//				}
//				i_panel.repaint();
//				i_panel.Initialize();
//			}
//		});
////=====================================================================================================
//// Title Label, just creates a label with the title on it centered and bolded
//		JLabel titleLabel = new JLabel("RPI Campus Map Path-Finder", SwingConstants.CENTER);
//		titleLabel.setFont(titleLabel.getFont().deriveFont(Font.BOLD, 24));
//		c.fill = GridBagConstraints.HORIZONTAL;
//		c.weightx = .9;
//		c.gridx = 0;
//		c.gridy = 0;
//		pane.add(titleLabel, c);
//
////=====================================================================================================
//// Starting ComboBox. It Displays a list of possible building comma seperated id pairs to the user
//// which they can select and have that value set to the Start Component. It also draws the start point
//// on the map
//		final JComboBox<String> Starting = new JComboBox<String>(choices);
//		if (shouldWeightX) {
//			c.weightx = 0.5;
//		}
//		c.fill = GridBagConstraints.HORIZONTAL; // Constraints
//		c.gridx = 0;
//		c.gridy = 2;
//		pane.add(Starting, c);
//		Starting.addActionListener(new ActionListener()
//		{
//			public void actionPerformed(ActionEvent e) { //Getting just the building name for the field
//				String choice = 
//						choices[Starting.getSelectedIndex()].substring(0, 
//								choices[Starting.getSelectedIndex()].indexOf(","));
//				Start.setText(choice);
//				i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start.getText())));
//				i_panel.repaint();
//			}
//		});
//
////=====================================================================================================
//// Ending ComboBox. It Displays a list of possible building comma seperated id pairs to the user
//// which they can select and have that value set to the End Component. It also draws the end point
//// on the map
//		final JComboBox<String> Ending = new JComboBox<String>(choices);
//		c.fill = GridBagConstraints.HORIZONTAL;
//		c.gridx = 1;
//		c.gridy = 2;
//		pane.add(Ending, c);
//		Ending.addActionListener(new ActionListener()
//		{
//			public void actionPerformed(ActionEvent e) {
//				String choice = 
//						choices[Ending.getSelectedIndex()].substring(0, 
//								choices[Ending.getSelectedIndex()].indexOf(","));
//				End.setText(choice);
//				i_panel.Set_End(CampusMap.get_Coord(CampusMap.get_ID(End.getText())));
//				i_panel.repaint();
//			}
//		});
//
////=====================================================================================================
////A button which displays the Text Path, similar to the one from the previous hw, hw7.
//// It checks if the input is valid, if not notifies the user with OptionPanes, same if there is no path
//// Otherwise it then creates an OptionPane with the path information.
//// Special Feature ~ I did some math on the side using Google Maps and pizel coordinates to determine
//// an approximate pixel to mile ratio, which I use alongside average human walking speed to display
//// an approximate distance and time it will take to reach the location.
//		JButton Text_Path = new JButton("Show Path in Text Form");
//		if (shouldWeightX) {
//			c.weightx = 0.5;
//		}
//		c.fill = GridBagConstraints.HORIZONTAL; // Define constraints
//		c.gridx = 0;
//		c.gridy = 5;
//		pane.add(Text_Path, c);
//		Text_Path.addActionListener(new ActionListener() // If button is pressed then...
//		{
//			public void actionPerformed(ActionEvent e) {
//				String Start_ = Start.getText();
//				String End_ = End.getText(); // Defined output if TextFields are unaltered
//				if(Start.getText().equals("Enter your Starting Location Here") ||
//						End.getText().equals("Enter your Ending Destination Here"))
//				{
//
//					String text = "Oops! You Forgot to Tell us Your Start/End Points\n"
//							+ "Don't forget to fill in both boxes.";
//					JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//							JOptionPane.INFORMATION_MESSAGE);
//				}
//				else
//				{ // Otherwise strips them, builds a path, and determines from the output if 
//					Start_ = strip(Start_); // The buildings exist or there is no path
//					End_ = strip(End_); // I could have used more Model functions than view functions
//					String Path = BuildingList.R_Command(Start_, End_, CampusMap); // But
//					if(Path.contains("Unknown building:")) // time constraints, it works though.
//					{
//						if(Start_.equals("Bella's Pizza"))
//						{
//							i_panel.ResetStart();
//							String text = "There is no better decision\nBut this is an Invalid Start "
//									+ "Location\nThis location is only for use with the Good Decision"
//									+ " Button";
//							JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//									JOptionPane.INFORMATION_MESSAGE);
//						}
//						else
//						{
//							i_panel.ResetStart();
//							String text = "Invalid Start Building\nPlease Enter a either a Building Name or "
//									+ "corresponding ID\n(Intersections are invalid input)";
//							JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//									JOptionPane.INFORMATION_MESSAGE);
//						}
//						if(!CampusMap.is_Building(End.getText()))
//						{
//							i_panel.ResetEnd();
//							String text = "Invalid End Building\nPlease Enter a either a "
//									+ "Building Name or"
//									+ " corresponding ID\n(Intersections are invalid input)";
//							JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//									JOptionPane.INFORMATION_MESSAGE);
//						}
//					}
//					else if(Path.contains("no path")) // Notifies user if no path available
//					{
//						i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//						i_panel.Set_End(CampusMap.get_Coord(CampusMap.get_ID(End_)));
//						i_panel.repaint();
//						String text = "Sorry, there is no path from " + Start_ + " to " + End_;
//						JOptionPane.showMessageDialog(null, text, "Route", 
//								JOptionPane.INFORMATION_MESSAGE);
//					}
//					else
//					{ // Notifies user if Start and End points are the same
//						if(Start_.equals(End_))
//						{
//							String text = "You are at your destination already!";
//							JOptionPane.showMessageDialog(null, text, "Route", 
//									JOptionPane.INFORMATION_MESSAGE);
//						}
//						else // Otherwise builds the path, calculates time/distance using my found
//						{    // and hard-coded in values
//						String Paths[] = Path.split("\n");
//						String text = "Starting at " + Start_ + "\n";
//						double distance = 0;
//						double time = 0;
//						for (int i = 1; i < Paths.length-1; i++)
//						{
//							text = text.concat(Paths[i]).concat("\n");
//						}
//						distance = Double.valueOf(Paths[Paths.length-1].substring(
//								Paths[Paths.length-1].indexOf(": ")+2, 
//								Paths[Paths.length-1].indexOf(" p")));
//						time = (float) distance/T_Conv;
//						distance = (float) distance/D_Conv; // Sets Start, End, Repaints
//						i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//						i_panel.Set_End(CampusMap.get_Coord(CampusMap.get_ID(End_))); 
//						i_panel.repaint();
//						text = text.concat("\n").concat(
//								String.format("Approximate Distance is %.3f miles\n", distance));
//						text = text.concat(
//								String.format("Approximate Time to Walk is %.2f minutes.\n", time));
//						// Opens the Pane with all of the information
//						JOptionPane.showMessageDialog(null, text, "Text Path", 
//								JOptionPane.INFORMATION_MESSAGE);
//						}
//					}
//				}
//			}
//		});
//
////=====================================================================================================
//// JButton that Also draws a path, with the same constraints and notifications to the user as
//// Text Path, but this time it draws lines on the map, and draws it as the title implies, step, by
//// step. Aka, it only adds one line at a time.
//		JButton Draw_Iterative = new JButton("Show Step-By-Step Path Animation"); // Constraints
//		c.fill = GridBagConstraints.HORIZONTAL;
//		c.gridx = 1;
//		c.gridy = 5;
//		pane.add(Draw_Iterative, c);
//		Draw_Iterative.addActionListener(new ActionListener()
//		{
//			public void actionPerformed(ActionEvent e) {
//				if(Start.getText().equals("Enter your Starting Location Here") ||
//						End.getText().equals("Enter your Ending Destination Here"))
//				{
//
//					String text = "Oops! You Forgot to Tell us Your Start/End Points\n"
//							+ "Don't forget to fill in both boxes.";
//					JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//							JOptionPane.INFORMATION_MESSAGE);
//				}
//				else // Same as Text Path
//				{
//					String Start_ = Start.getText();
//					String End_ = End.getText();
//					Start_ = strip(Start_);
//					End_ = strip(End_);
//					String Path = BuildingList.R_Command(Start_, End_, CampusMap);
//					if(Path.contains("Unknown building:"))
//					{
//						if(!CampusMap.is_Building(Start.getText()))
//						{
//							if(Start_.equals("Bella's Pizza"))
//							{
//							i_panel.ResetStart();
//							String text = "Invalid Start Building\nBella's Pizza is only for use"
//									+ " when determing if it is a good decision";
//							JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//										JOptionPane.INFORMATION_MESSAGE);
//							}
//							else
//							{
//							i_panel.ResetStart();
//							String text = "Invalid Start Building\nPlease Enter a either a Building "
//									+ "Name or corresponding ID\n(Intersections are invalid input)";
//							JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//									JOptionPane.INFORMATION_MESSAGE);
//							}
//						}
//						if(!CampusMap.is_Building(End.getText()))
//						{
//							i_panel.ResetEnd();
//							String text = "Invalid End Building\nPlease Enter a either a Building Name "
//									+ "or corresponding ID\n(Intersections are invalid input)";
//							JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//									JOptionPane.INFORMATION_MESSAGE);
//						}
//					}
//					else if(Path.contains("no path"))
//					{
//						i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//						i_panel.Set_End(CampusMap.get_Coord(CampusMap.get_ID(End_)));
//						i_panel.repaint();
//						String text = "Sorry, there is no path from " + Start_ + " to " + End_;
//						JOptionPane.showMessageDialog(null, text, "Route", 
//								JOptionPane.INFORMATION_MESSAGE);
//					}
//					else
//					{
//						if(Start_.equals(End_))
//						{
//							String text = "You are at your destination already!";
//							JOptionPane.showMessageDialog(null, text, "Route", 
//									JOptionPane.INFORMATION_MESSAGE);
//						}	
//						String[] Lines = Path.split("\n");
//						String temp;
//						Map.Entry<Double, Double> placeholder;
//						ArrayList<Map.Entry<Double, Double>> points = new ArrayList<Map.Entry<Double, Double>>();
//						placeholder = new AbstractMap.SimpleEntry<Double, Double> // Same as Text Path, but it does
//						(CampusMap.get_Coord(CampusMap.get_ID(Start_)).getKey(), // not calculate 
//								CampusMap.get_Coord(CampusMap.get_ID(Start_)).getValue()); // time	
//						points.add(placeholder); // or distance, here it creates variables used
//						i_panel.repaint(); // when building the path
//						i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//						i_panel.Set_End(CampusMap.get_Coord(CampusMap.get_ID(End_)));
//						for(int i = 1; i < Lines.length-1; i++) // Does some parsing
//						{
//							temp = Lines[i].substring(Lines[i].indexOf("(")+1, Lines[i].indexOf(")"));
//							if(temp.contains("Intersection"))
//							{
//								temp = temp.substring(temp.indexOf(" ")+1);
//							}
//							placeholder = new AbstractMap.SimpleEntry<Double, Double>
//							(CampusMap.get_Coord(CampusMap.get_ID(temp)).getKey(),
//									CampusMap.get_Coord(CampusMap.get_ID(temp)).getValue());
//							points.add(placeholder); // Draws the lines on at a time as it adds to
//							i_panel.Draw_lines(points); // the list
//							i_panel.Set_End(points.get(points.size()-1));
//							i_panel.paintImmediately(0, 0, i_panel.getWidth(), i_panel.getHeight());
//							try { // Sleeps so the user can watch
//								Thread.sleep(1000);
//							} catch (InterruptedException e1) {
//								// TODO Auto-generated catch block
//								e1.printStackTrace();
//							}
//						}
//						try {
//							Thread.sleep(500); // Sleeps a bit more at the end before path ultimately
//						} catch (InterruptedException e1) { // Disappears leaving only the end points
//							
//							e1.printStackTrace();
//						}
//						i_panel.Reset();
//						i_panel.Initialize();
//						i_panel.Draw_lines(points);
//						i_panel.paintImmediately(0, 0, i_panel.getWidth(), i_panel.getHeight());
//						i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//						i_panel.Set_End(CampusMap.get_Coord(CampusMap.get_ID(End_)));
//						i_panel.repaint(); // Finishes repainting etc.
//					}
//				}
//			}
//		});
////=====================================================================================================
//// User Defined Extra function. Takes the input in the start and finds you the fastest route to a 
//// good decision, as defined in the proof pdf saved to the repository. As such, it finds the shortest
//// route to Bella's, which is right next to Moe's. No file was edited, but Bella's Location hard-coded
//// in as a final static variable. Otherwise has same checks (minus end checks) as the Text_Path etc
//		JButton Pizza = new JButton("Fasest Route To a Good Decision");
//		if (shouldWeightX) {
//			c.weightx = 0.5;
//		}
//		c.fill = GridBagConstraints.HORIZONTAL;
//		c.gridx = 0;
//		c.gridwidth = 2;   //2 columns wide
//
//		c.gridy = 6;
//		pane.add(Pizza, c);
//		Pizza.addActionListener(new ActionListener()
//		{
//			public void actionPerformed(ActionEvent e) {
//				String Start_ = strip(Start.getText());
//				End.setText("Bella's Pizza"); // Sets dest. to Bella's
//				String End_ = End.getText();
//				i_panel.Set_End(Pizza_Loc);
//				i_panel.repaint();
//				if(!CampusMap.is_Building(Start_))
//				{
//					if(strip(Start_).equals("Bella's Pizza"))
//					{
//						String text = "There is No Better Decision";					
//						JOptionPane.showMessageDialog(null, text, "You're There", 
//								JOptionPane.INFORMATION_MESSAGE);
//					}
//					else
//					{
//						i_panel.ResetStart();
//					String text = "Invalid Start Building\nPlease Enter a either a Building Name or "
//							+ "corresponding ID\n(Intersections are invalid input)";					
//					JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//							JOptionPane.INFORMATION_MESSAGE);
//					}
//				}
//				else // Does some path building using findPath
//				{
//				i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//				ArrayList<String> P = new ArrayList<String>  // Always goes to 100 since its next to
//					(CampusMap.findPath(CampusMap.get_ID(strip(Start.getText())), "100")); // Bella's
//				String path = "";
//				double path_L = 0.00;
//				String angle;
//				String temp1 = CampusMap.get_Building(strip(Start.getText()));
//				String temp2 = CampusMap.get_Building("Bella's");   
//				// Reconstructs the path
//				if(P.isEmpty())
//				{
//					path = path.concat("There is no path from " +  temp1 + " to " + temp2 + ".");
//				}
//				else
//				{
//					path = path.concat("Path from " + temp1 + " to " + temp2 + ":\n"); 
//					for(int i = 0; i < P.size(); i += 3)
//					{
//						if(CampusMap.is_Building(P.get(i+1)))
//						{
//							temp1 = "(".concat(CampusMap.get_Building(P.get(i+1))).concat(")");
//						}
//						if(!CampusMap.is_Building(P.get(i+1)))
//						{
//							temp1 = "(Intersection ".concat(CampusMap.get_ID(P.get(i+1))).concat(")");
//						}
//						angle = BuildingList.findDirection(CampusMap.find_Angle(P.get(i), P.get(i+1)));
//						path = path.concat("\tWalk " + angle + " to " +  temp1 + "\n");
//						path_L += Double.valueOf(P.get(i+2));
//					}
//					path = path.concat(String.format("Total distance: %.3f pixel units.", path_L));
//				}
//				// Parses the path
//				if(path.contains("no path"))
//				{
//					i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//					i_panel.Set_End(CampusMap.get_Coord(CampusMap.get_ID(End_)));
//					i_panel.repaint();
//					String text = "Sorry, there is no path from " + Start_ + " to " + End_;
//					JOptionPane.showMessageDialog(null, text, "Route", 
//							JOptionPane.INFORMATION_MESSAGE);
//				}
//				else
//				{
//					if(Start_.equals(End_))
//					{
//						String text = "You are at your destination already!";
//						JOptionPane.showMessageDialog(null, text, "Route", 
//								JOptionPane.INFORMATION_MESSAGE);
//					}	
//					String[] Lines = path.split("\n");
//					String temp; // Draws the path
//					Map.Entry<Double, Double> placeholder;
//					ArrayList<Map.Entry<Double, Double>> points = new ArrayList<Map.Entry<Double, Double>>();
//					placeholder = new AbstractMap.SimpleEntry<Double, Double>
//					(CampusMap.get_Coord(CampusMap.get_ID(Start_)).getKey(),
//							CampusMap.get_Coord(CampusMap.get_ID(Start_)).getValue());				
//					points.add(placeholder);
//					for(int i = 1; i < Lines.length-1; i++)
//					{
//						temp = Lines[i].substring(Lines[i].indexOf("(")+1, Lines[i].indexOf(")"));
//						if(temp.contains("Intersection"))
//						{
//							temp = temp.substring(temp.indexOf(" ")+1);
//						}
//						placeholder = new AbstractMap.SimpleEntry<Double, Double>
//						(CampusMap.get_Coord(CampusMap.get_ID(temp)).getKey(),
//								CampusMap.get_Coord(CampusMap.get_ID(temp)).getValue());
//						points.add(placeholder);
//					} // Adds final Dest. Pizza_Loc
//					points.add(Pizza_Loc);
//					i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//					i_panel.Set_End(Pizza_Loc);
//	
//					i_panel.repaint();
//					i_panel.Initialize();
//
//					i_panel.Draw_lines(points);
//					i_panel.repaint(); // Finishes Drawing and painting
//					
//					double distance = Double.valueOf(Lines[Lines.length-1].substring(
//							Lines[Lines.length-1].indexOf(": ")+2, 
//							Lines[Lines.length-1].indexOf(" p")));
//					double time = (float) distance/T_Conv;
//					distance = (float) distance/D_Conv;
//					String text = "";
//					text = text.concat("\n").concat(
//							String.format("Approximate Distance is %.3f miles\n", distance));
//					text = text.concat(
//							String.format("Approximate Time to Walk is %.2f minutes.\n", time));
//					
//					JOptionPane.showMessageDialog(null, text, "Pizza Statistics", 
//							JOptionPane.INFORMATION_MESSAGE);
//				}
//				}
//			}
//		});
////=====================================================================================================
//// Button to Quit out, just calls System.Exit since the program is the GUI
//		JButton Quit = new JButton("Quit");
//		c.weightx = 0.5;
//		c.fill = GridBagConstraints.HORIZONTAL;
//		c.gridx = 2;
//		c.gridwidth = 2;   //2 columns wide
//
//		c.gridy = 6;
//		pane.add(Quit, c);
//		Quit.addActionListener(new ActionListener()
//		{
//			public void actionPerformed(ActionEvent e) {
//				System.exit(0);
//			}
//		});
////=====================================================================================================
//// Help Button, prints instructions on how to use the GUI in an OptionPane
//		JButton Help = new JButton("?");
//		c.weightx = 0.4;
//		c.fill = GridBagConstraints.HORIZONTAL;
//		c.gridx = 2;
//		c.gridy = 0;
//		pane.add(Help, c);
//		Help.addActionListener(new ActionListener()
//		{ // Help Text, it is quite large.
//		String HelpText = ""
//				+ "The 'Enter your Starting Location Here' Box is used by inputting in the requested"
//				+ " 1. Building Name or it's respective ID. Be Careful, you can only input one and it is"
//				+ " case sensitive! \nAlso, when enter is pressed, if the Name/ID is valid, a green"
//				+ " circle will appear on the map next over the building. This is the starting"
//				+ " location of the path.\n\n"
//				+ " 2. The 'Enter your Ending Destination Here' Box is exactly the same as the Starting"
//				+ " Box. The only difference is it is used for your ending destination and a red"
//				+ " circle appears on the map. \n\n"
//				+ " 3. The DropDown Boxes below are an easy way to see a list of all of the Buildings,"
//				+ " next to each is their respective ID, input either \n  or select them from the menu"
//				+ " to insure you are using coordinates this tool can understand!\n\n"
//				+ " 4. The 'Find Path from Starting Location to Ending Destination' Button is used"
//				+ "when you have inputted a Start Location and End Destionaton in the boxes above"
//				+ " then, when this button is pressed, \n  a route will appear on the map showing the"
//				+ " path you requested. If a text box appears, something is wrong, read the box "
//				+ " to find out.\n\n"
//				+ " 5. You can also select the 'Show Step-By-Step Animation Button, which works the same"
//				+ " as the previous one, except it shows the path more slowly, as if you were"
//				+ " walking it.\n\n"
//				+ " 6. The 'Show Path in Text Form' Button works the same way as the previous ones,"
//				+ " the only difference is the path is shown in words instead of on the map! \nThere"
//				+ " is also a distance and time approximation for your convienance!\n\n"
//				+ " 7. The Reset button is used to return the tool to the state it was when you started"
//				+ " it, just in case you need an undo button.\n\n"
//				+ " 8. And Finally, just in case you were in need a good decision, there is a "
//				+ " 'Fastest Route to a Good Decision' Button Handy. This Button will take wherever"
//				+ " you are and find you the \nfastest route to Bella's Pizzaria. It also will give"
//				+ " an approximation on how long it will take and how far it is.\n\n"
//				+ " 9. The '?' Button gives you help! And, the Quit Button in case you haven't"
//				+ " guessed, quits out of the tool.\n\n Goodluck"
//				+ " Finding Your Way! May you never be lost again!!!";
//			public void actionPerformed(ActionEvent e) {
//				JOptionPane.showMessageDialog(null, HelpText, "Help Menu", 
//						JOptionPane.INFORMATION_MESSAGE);
//			}
//		});
////=====================================================================================================
//// Defines and adds the image pane which was created above
//		c.fill = GridBagConstraints.BOTH;
//		c.ipady = 560;
//		c.weightx = 1.0;
//		c.gridwidth = 5;
//		c.gridx = 0;
//		c.gridy = 3;
//		c.insets = new Insets(0,52,0,0);  //top padding
//		pane.add(i_panel, c);
////=====================================================================================================
//// What the other path buttons are based on, this does the same as Iterative_Path but all at once
//		JButton Calculate = new JButton("Find Path from Starting Location to Ending Destination");
//		c.fill = GridBagConstraints.HORIZONTAL;
//		c.ipady = 0;       
//		c.insets = new Insets(0,0,0,0);  
//		c.gridx = 0;      // Define Constraints, do the same as others
//		c.gridwidth = 2;
//		c.gridy = 4;     
//		pane.add(Calculate, c);
//
//		Calculate.addActionListener(new ActionListener()
//		{
//			public void actionPerformed(ActionEvent e) {
//				if(Start.getText().equals("Enter your Starting Location Here") ||
//						End.getText().equals("Enter your Ending Destination Here"))
//				{
//					i_panel.ResetStart();
//					i_panel.ResetEnd();
//					String text = "Oops! You Forgot to Tell us Your Start/End Points\n"
//							+ "Don't forget to fill in both boxes.";
//					JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//							JOptionPane.INFORMATION_MESSAGE);
//				}
//				else
//				{
//					String Start_ = Start.getText();
//					String End_ = End.getText();
//					Start_ = strip(Start_);
//					End_ = strip(End_);
//					String Path = BuildingList.R_Command(Start_, End_, CampusMap);
//					if(Path.contains("Unknown building:"))
//					{
//						if(!CampusMap.is_Building(Start.getText()))
//						{
//							i_panel.ResetStart();
//							String text = "Invalid Start Building\nPlease Enter a either a Building Name or "
//									+ "corresponding ID\n(Intersections are invalid input)";
//							JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//									JOptionPane.INFORMATION_MESSAGE);
//						}
//						if(!CampusMap.is_Building(End.getText()))
//						{
//							i_panel.ResetEnd();
//							String text = "Invalid End Building\nPlease Enter a either a Building Name or"
//									+ " corresponding ID\n(Intersections are invalid input)";
//							JOptionPane.showMessageDialog(null, text, "Invalid Input", 
//									JOptionPane.INFORMATION_MESSAGE);
//						}
//					}
//					else if(Path.contains("no path"))
//					{
//						i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//						i_panel.Set_End(CampusMap.get_Coord(CampusMap.get_ID(End_)));
//						i_panel.repaint();
//						String text = "Sorry, there is no path from " + Start_ + " to " + End_;
//						JOptionPane.showMessageDialog(null, text, "Route", JOptionPane.INFORMATION_MESSAGE);
//					}
//					else
//					{
//						if(Start_.equals(End_))
//						{
//							String text = "You are at your destination already!";
//							JOptionPane.showMessageDialog(null, text, "Route", JOptionPane.INFORMATION_MESSAGE);
//						}	
//						String[] Lines = Path.split("\n");
//						String temp;
//						Map.Entry<Double, Double> placeholder;
//						ArrayList<Map.Entry<Double, Double>> points = new ArrayList<Map.Entry<Double, Double>>();
//						placeholder = new AbstractMap.SimpleEntry<Double, Double>
//						(CampusMap.get_Coord(CampusMap.get_ID(Start_)).getKey(),
//								CampusMap.get_Coord(CampusMap.get_ID(Start_)).getValue());				
//						points.add(placeholder);
//						for(int i = 1; i < Lines.length-1; i++)
//						{
//							temp = Lines[i].substring(Lines[i].indexOf("(")+1, Lines[i].indexOf(")"));
//							if(temp.contains("Intersection"))
//							{
//								temp = temp.substring(temp.indexOf(" ")+1);
//							}
//							placeholder = new AbstractMap.SimpleEntry<Double, Double>
//							(CampusMap.get_Coord(CampusMap.get_ID(temp)).getKey(),
//									CampusMap.get_Coord(CampusMap.get_ID(temp)).getValue());
//							points.add(placeholder);
//						}
//						// Draws it all at once instead of iteratively
//						i_panel.Set_Start(CampusMap.get_Coord(CampusMap.get_ID(Start_)));
//						i_panel.Set_End(CampusMap.get_Coord(CampusMap.get_ID(End_)));
//		
//						i_panel.repaint();
//						i_panel.Initialize();
//
//						i_panel.Draw_lines(points);
//						i_panel.repaint();
//					}
//				}
//			}
//		});
////=====================================================================================================
//// Reset button resets everything to defaults using reset methods etc.
//		Reset.setText("Reset");
//		c.fill = GridBagConstraints.HORIZONTAL;
//		c.ipady = 0;   
//		c.gridx = 2;
//		c.gridy = 5;       
//		pane.add(Reset, c);
//		Reset.addActionListener(new ActionListener()
//		{
//			public void actionPerformed(ActionEvent e) {
//				Starting.setSelectedIndex(0);
//				Ending.setSelectedIndex(0);
//				i_panel.Reset();
//				i_panel.Initialize();
//				i_panel.repaint();
//				Start.setText("Enter your Starting Location Here");
//				End.setText("Enter your Ending Destination Here");
//			}
//		});
//	}
//// End of the Components and addComponentstoPane Class
////=====================================================================================================
//
//	/**
//	 * @param String input to be stripped of all trailing whitespace
//	 * @returns returns input but without any trailing whitespace
//	 * @throws N/A
//	 * @requires N/A
//	 * @modifies N/A
//	 * @effects N/A
//	 */
//	private static String strip(String input)
//	{
//		String input_ = input;
//		while(input_.endsWith(" "))
//		{
//			input_ = input_.substring(0, input_.lastIndexOf(" "));
//		}				
//		return input_;
//	}
//	/**
//	 * @param N/A
//	 * @returns N/A
//	 * @throws N/A
//	 * @requires N/A
//	 * @modifies JFrame frame
//	 * @effects creates a visible frame window with components added to it using map data.
//	 */
//	private static void createAndShowGUI() {
//		//Create and set up the window.
//		JFrame frame = new JFrame("RPI Campus Map Path-Finder Tool");
//		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//		frame.setMinimumSize(new Dimension(768,768)); // Make it so you can't ruin the window
//		frame.setPreferredSize(new Dimension(768,768));; // I need the window to fit on a 1024x768
//		//Screen, so, since I am not resizing it, why not just make a bit smaller than the size I need.
//		String nodes_file = "data/RPI_map_data_Nodes.csv";//Hardcode in the files since that was asked
//		String edge_file = "data/RPI_map_data_Edges.csv";
//		CampusModel CampusMap = new CampusModel(); // Makes a new object and creates the graph
//		CampusMap.createNewGraph(nodes_file, edge_file);
//		JButton Reset = new JButton(); // Button I need to pass, explained at the bottom
//		//Set up the content pane.
//		addComponentsToPane(frame.getContentPane(), CampusMap, Reset);
//
//		//Display the window.
//		frame.pack();
//		frame.setVisible(true);
//		Reset.doClick(); // I want to use getScaledInstance of an image, but you need a width/height of
//		// a window to do so, also calling it in paintComponent is a big-no-no with an infinite loop,
//		// so I get around that by passing it my reset button which has no effect since it just sets
//		// it back to its default state.
//	}
//
//	public static void main(String[] args) {
//		createAndShowGUI(); // Creates the GUI, it is so short because GUI is essentially a view
//		// as such I defined it to its own class
//	}
//}