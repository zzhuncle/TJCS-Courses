
`timescale 1ns / 1ps
module DIV(//32λ�з��Ų��ָ�����������
    input [31 : 0] dividend,//������
    input [31 : 0] divisor,//����
    input start,//������������           
    input clock,
    input reset,//�ߵ�ƽ��Ч
    output [31 : 0] q,//��
    output [31 : 0] r,//����     
    output reg busy//������æ��־λ
);
	wire ready;
	reg [4 : 0] count;
	reg [31 : 0] reg_q;//��
	reg [31 : 0] reg_r;//����
	reg [31 : 0] reg_b;//����
	wire [31 : 0] reg_r2;
	reg busy2, r_sign;
	assign ready = ~busy & busy2;//ʱ�������
	//�ӡ�������
	//r_signΪ0��˵��������Ϊ����r_signΪ1��˵��������Ϊ��
	wire [32 : 0] sub_add = r_sign ? ({reg_r, reg_q[31]} + {1'b0, reg_b}) : ({reg_r, reg_q[31]} - {1'b0, reg_b});
	assign reg_r2 = r_sign ? reg_r + reg_b : reg_r;
	assign r = dividend[31] ? (~reg_r2 + 1) : reg_r2;//����
    assign q = (divisor[31] ^ dividend[31]) ? (~reg_q + 1) : reg_q;//��
	always @ (posedge clock or posedge reset) begin
		if (reset) begin//����
			count <= 5'b0;
			busy <= 0;
			busy2 <= 0;
		end else begin
			busy2 <= busy;
			if (start) begin//��ʼ�������㣬��ʼ��
				reg_r <= 32'b0;
				r_sign <= 0;
				reg_q <= dividend[31] ? ~dividend + 1 : dividend;//��������ֵ����
				reg_b <= divisor[31] ? ~divisor + 1 : divisor;//������ֵ������
				count <= 5'b0;
				busy <= 1'b1;
			end else if (busy) begin//ѭ������
				reg_r <= sub_add[31 : 0];//��������
				r_sign <= sub_add[32];//���Ϊ�����´����
				reg_q <= {reg_q[30 : 0], ~sub_add[32]};
				count <= count + 5'b1;//��������1
				if (count == 5'b11111) 
					busy <= 0; 
			end//������������ 
		end
	end
endmodule