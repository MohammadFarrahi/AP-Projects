#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

#define ZERO 0
#define EMPTY 0
#define VISITED 1
#define UNVISITED 0
#define MAX_MOVEMENT_POSSIBLE 4

struct Fields_Info {
int row;
int col;  
};

struct Valid_Cells {
vector<int> row;
vector<int> col;
};

typedef vector<vector<int> > Area;


bool Is_out(Fields_Info fields_info,int i,int j){

    if(i<ZERO||j<ZERO||i>=fields_info.row||j>=fields_info.col)
    	return true;

    return false;
}

bool Is_forbidden(const Area& golden_area,const Area& checked_fields,int i,int j){

	if(checked_fields[i][j]==VISITED||golden_area[i][j]==EMPTY)
		return true;

	return false;
}

bool Is_valid(const Area& golden_area,const Area& checked_fields,Fields_Info fields_info,int i,int j){

	if(!Is_out(fields_info,i,j) && !Is_forbidden(golden_area,checked_fields,i,j))
		return true;

	return false;
}

Fields_Info get_row_and_col(void){

	Fields_Info fields_info;

	cin>>fields_info.row>>fields_info.col;

	return fields_info;
}

void get_amounts_of_fields(Area& golden_area,Fields_Info fields_info,int Is_LastRow=ZERO){

	if(Is_LastRow==fields_info.row)
		return;

	vector<int> fields_in_one_row(fields_info.col);

	for(int index=ZERO;index<fields_info.col;index++)
		cin>>fields_in_one_row[index];

	get_amounts_of_fields(golden_area,fields_info,++Is_LastRow);

    golden_area.insert(golden_area.begin(),fields_in_one_row);
}

void find_valid_indexs_to_begin(const Area& golden_area,Fields_Info fields_info ,Valid_Cells& fields_to_begin_process,int row_index=0){

if(row_index==fields_info.row)
	return;

	for(int col_index=0;col_index<fields_info.col;col_index++){

		if(golden_area[row_index][col_index]!=EMPTY){
          fields_to_begin_process.row.push_back(row_index);
          fields_to_begin_process.col.push_back(col_index);
		}
	}
  find_valid_indexs_to_begin(golden_area,fields_info,fields_to_begin_process,++row_index);

}

void find_max_amount_of_gold(const Area& golden_area, Area& checked_fields, Fields_Info fields_info, const Valid_Cells& fields_to_begin_process,
	int curr_pos_row, int curr_pos_col, unsigned int& max_amount, int field_process_counter=0, unsigned int current_amount=0){

    int row_of_movement[]={-1,0,1,0};
    int col_of_movment[]={0,1,0,-1};
	int unable_to_move=0;

	checked_fields[curr_pos_row][curr_pos_col] = VISITED;
	current_amount += golden_area[curr_pos_row][curr_pos_col];

	for(int move_direction=0; move_direction < MAX_MOVEMENT_POSSIBLE; move_direction++){
 
		if(Is_valid(golden_area, checked_fields, fields_info, curr_pos_row + row_of_movement[move_direction], curr_pos_col + col_of_movment[move_direction]))

			find_max_amount_of_gold(golden_area, checked_fields, fields_info, fields_to_begin_process, curr_pos_row + row_of_movement[move_direction],
				curr_pos_col + col_of_movment[move_direction], max_amount, field_process_counter, current_amount);

		else
			unable_to_move++;
	}

	checked_fields[curr_pos_row][curr_pos_col] = UNVISITED;
	if(unable_to_move == MAX_MOVEMENT_POSSIBLE)
		max_amount = max(current_amount, max_amount);

	if(fields_to_begin_process.row[field_process_counter] == curr_pos_row && fields_to_begin_process.col[field_process_counter] == curr_pos_col)
		if(field_process_counter < fields_to_begin_process.row.size()){
            
            field_process_counter++;
			find_max_amount_of_gold(golden_area, checked_fields, fields_info, fields_to_begin_process,
			fields_to_begin_process.row[field_process_counter], fields_to_begin_process.col[field_process_counter], max_amount, field_process_counter);
  }
}

int main(){

Fields_Info fields_info= get_row_and_col();
Valid_Cells fields_to_begin_process;
Area golden_area;
unsigned int max_amount=ZERO;

Area checked_fields (fields_info.row, vector<int> (fields_info.col,UNVISITED));
get_amounts_of_fields(golden_area,fields_info);

find_valid_indexs_to_begin(golden_area,fields_info,fields_to_begin_process);


find_max_amount_of_gold(golden_area,checked_fields,fields_info,fields_to_begin_process,
 fields_to_begin_process.row[ZERO],fields_to_begin_process.col[ZERO],max_amount);

cout<<max_amount;
	return ZERO;
}